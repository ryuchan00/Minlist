// cwsの形式で割り当て表を作成する
//
/*Min Hashベースのマルチセットの近似解法*/

/*
 先行研究論文
 Xu, X., Gao, C., Pei, J., Wang, K., Al-Barakati, A.: Continuous similarity
 search for evolving queries. Knowl. Inf. Syst. 48(3), 649–678 (2016)
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ./MHI4 database.txt queri.txt シード値　SWの数　Minhash.txt マルチセットの上限 出力ファイル名//
// 元データの要素をランダムに組み合わせてデータベースを作る関数                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <cstdlib>

#include "contents.h"
#include "kyotsu.h"
#include "minhash.h"

#define DEBUG

#define PERIOD (100000)
using namespace std;

int mh(vector<int> c, vector<int> hash_table1, vector<int> hash_table2) {
  int count = 0;
  int vm = hash_table1.size();
  for (int i = 1; i < hash_table2.size(); i++) {
    for (int j = 0; j < vm; j++) {
      count += 1;
      auto result = find(c.begin(), c.end(), hash_table1[j] + hash_table2[i] * vm);
      // 見つかった場合
      if (result != c.end()) {
        return count;
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int t = 0;

  vector<int> database;                  //データベース
  char *dbname = argv[1];                // database.txt
  database = readdatabase_line(dbname);  //データベース作成

  /*パラメータ*/
  int w = atoi(argv[2]);  //ウインドウサイズ
  int dmax = PERIOD + w;  //ストリームデータの長さ

  vector<vector<int>> minhash;
  vector<int>::iterator it;

  char *mhname = argv[3];              // Minhash.txt
  minhash = readminhash(mhname);       //ハッシュ関数の読み込み
  int num_of_hash = minhash.size();    //ハッシュ関数の数
  int multi = atoi(argv[4]);           // wの中の要素の数の上限
  int vm = minhash[0].size() - multi;  //要素の種類数
  int vmw = vm * multi;                //要素種類数 × 多重度の数
  int search_limit = atoi(argv[5]);    // delete_val探索時の探索回数
#ifdef DEBUG
  /* 乱数SEED設定 */
  srand((int)time(NULL));
  int sample_t1 = rand() % dmax;
  int sample_t2 = rand() % dmax;
  vector<vector<int>> sampled_hash_list_t1(num_of_hash);
  vector<vector<int>> sampled_hash_list_t2(num_of_hash);
#endif

  ////////////////////////////////////////////////////////////////
  /*Min-hashに用いるランダムの値のテーブル*/
  /*要素の種類の配列*/
  vector<vector<int>> fx_a(num_of_hash, vector<int>(vm));

  for (int l = 0; l < num_of_hash; l++) {
    for (int i = 0; i < vm; i++) {
      fx_a[l][i] = minhash[l][i];
    }
  }

  /*多重度の配列*/
  // fx_bは、以後に最小値候補とならない値については書き換えを行っているため、比較のためにmulti+1の要素数が必要
  // 実際に計算に使用する要素は1から
  vector<vector<int>> fx_b(num_of_hash, vector<int>(multi + 1, 5000000));

  for (int l = 0; l < num_of_hash; l++) {
    for (int s = 1; s <= multi; s++) {
      int Allocation_s = minhash[l][(multi + (s - 1))];  //アルファベットに対してs番目の割り当て値
      if (Allocation_s > fx_b[l][s - 1]) {
        fx_b[l][s] = fx_b[l][s - 1];
      } else {
        fx_b[l][s] = Allocation_s;
      }
    }
  }

  ////////////////////////////////////////////////////////////////

  /*残っている要素のリストとスライディングウインドウに含まれている数のヒストグラムの作成*/

  vector<vector<contents>> Minlist(num_of_hash);  //残っている要素のリスト[ハッシュ関数][残ってる要素]
  vector<int> histgram(vm);                       // histgramは個数のみを持つ
  vector<std::array<int, 1>> ar(vm, {-1});        // 固定長で試してみる
  // vector<vector> でも固定長を定義できる

  vector<int> reset_count(num_of_hash, 0);

  int In;  //データストリームに入ってくる一番新しい要素

  //最小値
  struct contents a;
  a.label = 99999;
  a.value = 5000000;
  vector<contents> min_elem(num_of_hash, a);

  int same_count = 0;
  int another_count = 0;
  int out_count = 0;
  //ここから時刻による更新

  double ave_length, time_ave_length, sum_time_ave_length = 0.0;
  clock_t start = clock();  //ここから時間を測る

  while (t < dmax) {
    //出ていく処理
    if (t >= w) {
      int out = database[t - w];
      histgram[out]--;
      if (ar[out][0] == (t - w)) {
        ar[out][0] = ar[out][1];
        ar[out][1] = -1;
      }
      double sum_length = 0;
      for (int l = 0; l < num_of_hash; l++) {
        sum_length += Minlist[l].size();
        if (Minlist[l][0].time == t - w) {
          Minlist[l].erase(Minlist[l].begin());
          out_count++;
        }
        if (out == min_elem[l].label) {
          //最小値と同じラベルがストリームデータから出ていく時
          int min = 5000000;
          int m_label;
          for (int m = 0; m < Minlist[l].size(); m++) {
            int Minlist_value = Minlist[l][m].value;

            if (min > Minlist_value) {
              //最小値を調べる
              int label = Minlist[l][m].label;
              int value_check = fx_a[l][label] + fx_b[l][histgram[label]] * vm;

              if (Minlist_value == value_check) {
                //割り当て値に間違いがない場合
                min = Minlist_value;
                m_label = label;
              } else {
                Minlist[l][m].value = value_check;
                if (min > value_check) {
                  //割り当て値が間違っている場合
                  min = value_check;
                  m_label = label;
                }
              }
            }
          }
          min_elem[l].value = min;
          min_elem[l].label = m_label;
        }
      }
      time_ave_length = sum_length / (double)num_of_hash;
      sum_time_ave_length += time_ave_length;
    }
    //入っていく処理////////////////
    In = database[t];
    histgram[In]++;

    for (int l = 0; l < num_of_hash; l++) {
      int in_value = fx_a[l][In] + fx_b[l][histgram[In]] * vm;  // 現在入ってきた要素の値
#ifdef DEBUG
      if ((sample_t1 <= t) && (t <= (sample_t1 + w))) {
        sampled_hash_list_t1[l].push_back(in_value);
      }
      if ((sample_t2 <= t) && (t <= (sample_t2 + w))) {
        sampled_hash_list_t2[l].push_back(in_value);
      }
#endif
      int delete_val = 0;  // 1番目の値
      int m = Minlist[l].size() - 1;
      int back_IN_num = 0;  // 後方にあるhist_max_labelの要素数
      int pointer = 0;
      int hist_time = t;

      while (m >= 0) {
        // Minlistのスキャン
        if (Minlist[l][m].label == In) {
          //同じラベルのを消す
          Minlist[l].erase(Minlist[l].begin() + m);
          same_count++;
        } else {
          while (Minlist[l][m].time < hist_time) {
            //時刻によって判断
            back_IN_num++;
            delete_val = fx_a[l][In] + fx_b[l][back_IN_num] * vm;

            // back_IN_num=引数であたえられた値のとき、hist_timeの更新はこれ以上必要ない。
            if (back_IN_num >= search_limit) {
              hist_time = -1;
              break;
            }

            if (ar[In][0] != -1) {
              hist_time = ar[In][0];
              ar[In][0] = -1;
            } else {
              hist_time = -1;
            }
          }
          if (Minlist[l][m].value >= delete_val) {
            //値を比べる
            Minlist[l].erase(Minlist[l].begin() + m);
            another_count++;
          }
        }
        m--;
      }
      a.label = In;
      a.time = t;
      a.value = in_value;
      Minlist[l].push_back(a);

      if (min_elem[l].value > in_value) {
        //最小値の更新
        min_elem[l].value = in_value;
        min_elem[l].label = In;
      }
    }
    ar[In][0] = t;
    t++;
  }

  ave_length = sum_time_ave_length / t;
  cout << ave_length << "\n";

  cout << "same= " << same_count << " anohter= " << another_count << " out= " << out_count << "\n";
  clock_t end = clock();  //ここまで時間測定

  double match_count = 0.0;
#ifdef DEBUG
  for (int i; i < num_of_hash; i++) {
    if (mh(sampled_hash_list_t1[i], fx_a[i], fx_b[i]) == mh(sampled_hash_list_t2[i], fx_a[i], fx_b[i])) {
      match_count++;
    }
  }

  // 厳密なjaccard係数を求める
  vector<vector<int>> intersection(num_of_hash);
  vector<vector<int>> unions(num_of_hash);
  double sum;
  for (int i; i < num_of_hash; i++) {
    sort(sampled_hash_list_t1[i].begin(), sampled_hash_list_t1[i].end());
    sort(sampled_hash_list_t2[i].begin(), sampled_hash_list_t2[i].end());

    // a と b の積集合を得る
    set_intersection(sampled_hash_list_t1[i].begin(), sampled_hash_list_t1[i].end(), sampled_hash_list_t2[i].begin(), sampled_hash_list_t2[i].end(), back_inserter(intersection[i]));

    // aとbの和集合を作る
    set_union(sampled_hash_list_t1[i].begin(), sampled_hash_list_t1[i].end(), sampled_hash_list_t2[i].begin(), sampled_hash_list_t2[i].end(), inserter(unions[i], std::end(unions[i])));

    sum += (double)intersection[i].size() / unions[i].size();
  }
  cout << "jaccard: " << (match_count / num_of_hash) << endl;
  cout << "厳密なjaccard: " << (sum / num_of_hash) << endl;
#endif
  cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
  return 0;
}
