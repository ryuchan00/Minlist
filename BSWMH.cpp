/*Min Hashベースのマルチセットの近似解法*/

/*
 先行研究論文
 Xu, X., Gao, C., Pei, J., Wang, K., Al-Barakati, A.: Continuous similarity
 search for evolving queries. Knowl. Inf. Syst. 48(3), 649–678 (2016)
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ./MHI4 database.txt　SWの数　Minhash.txt マルチセットの上限 更新の間隔//
// 元データの要素をランダムに組み合わせてデータベースを作る関数                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "contents.h"
#include "kyotsu.h"
#include "minhash.h"

//#define DEBUG

#define PERIOD (100000)  //時刻
#define SW_length (100)
using namespace std;

int main(int argc, char* argv[]) {
  int t = 0;

  vector<int> database;                  //データベース
  char* dbname = argv[1];                // database.txt
  database = readdatabase_line(dbname);  //データベース作成
  cout << database.size() << endl;

  /*パラメータ*/
  int w = atoi(argv[2]);  //ウインドウサイズ

  vector<vector<int> > minhash;
  vector<int>::iterator it;

  char* mhname = argv[3];            // Minhash.txt
  minhash = readminhash(mhname);     //ハッシュ関数の読み込み
  int num_of_hash = minhash.size();  //ハッシュ関数の数
  int vmw = minhash[0].size();       //要素種類数 × 多重度の数
  int multi = atoi(argv[4]);         // wの中の要素の数の上限

  int interval = atoi(argv[5]);        //更新の間隔
  int vm = vmw / multi;                //要素の種類数
  int dmax = (PERIOD + w) / interval;  //ストリームデータの長さ
  ////////////////////////////////////////////////////////////////
  /*Min-hashに用いるランダムの値のテーブル*/

  vector<vector<vector<int> > > fx(num_of_hash, vector<vector<int> >(vm, vector<int>(multi + 1, 5000000)));

  for (int l = 0; l < num_of_hash; l++) {
    for (int i = 0; i < vm; i++) {
      for (int s = 1; s <= multi; s++) {
        int Allocation_s = minhash[l][i + (vm * (s - 1))];  //アルファベットに対してs番目の割り当て値
        if (Allocation_s > fx[l][i][s - 1]) {
          fx[l][i][s] = fx[l][i][s - 1];
        } else {
          fx[l][i][s] = Allocation_s;
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////

  /*残っている要素のリストとスライディングウインドウに含まれている数のヒストグラムの作成*/

  vector<vector<contents> > Minlist(num_of_hash);  //残っている要素のリスト[ハッシュ関数][残ってる要素]
  vector<deque<int> > histgram(vm);                //要素数0,初期値0

  int In;  //データストリームに入ってくる一番新しい要素

  //最小値
  struct contents a;
  a.label = 99999;
  a.value = 5000000;
  vector<contents> min_elem(num_of_hash, a);

  int same_count = 0;
  int another_count = 0;
  int out_count = 0;
  int t_a;
  //ここから時刻による更新

  double ave_length, time_ave_length, sum_time_ave_length = 0.0;
  clock_t start = clock();  //ここから時間を測る
  // cout<<"A"<<"\n";
  while (t < dmax) {
    // double Min_ave=0;
    //出ていく処理
    if (t * interval >= w) {
      for (int x = 0; x < interval; x++) {
        t_a = t * interval + x;
        int out = database[t_a - w];
        ;
        histgram[out].erase(histgram[out].begin());
        double sum_length = 0;
        for (int l = 0; l < num_of_hash; l++) {
          sum_length += Minlist[l].size();
          if (Minlist[l][0].time == t_a - w) {
            Minlist[l].erase(Minlist[l].begin());
            out_count++;
          }
          if (out == min_elem[l].label) {  //最小値と同じラベルがストリームデータから出ていく時

            int min = 5000000;
            int m_label;
            for (int m = 0; m < Minlist[l].size(); m++) {
              int Minlist_value = Minlist[l][m].value;

              if (min > Minlist_value) {  //最小値を調べる

                int label = Minlist[l][m].label;
                int value_check = fx[l][label][histgram[label].size()];

                if (Minlist_value == value_check) {  //割り当て値に間違いがない場合
                  min = Minlist_value;
                  m_label = label;
                } else {
                  Minlist[l][m].value = value_check;
                  if (min > value_check) {  //割り当て値が間違っている場合
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

        if (x == 0) {
          time_ave_length = sum_length / (double)num_of_hash;
          sum_time_ave_length += time_ave_length;
        }
      }
    }

    //入っていく処理////////////////

    vector<int> tmplist;  //入って来た要素の集合
    int In;
    for (int x = 0; x < interval; x++) {
      t_a = t * interval + x;
      In = database[t_a];
      histgram[In].push_back(t_a);
      tmplist.push_back(In);
    }

    for (int l = 0; l < num_of_hash; l++) {
      int in_value = fx[l][In][histgram[In].size()];  //一番最後に入ってきた要素の値

      for (int x = 0; x < interval - 1; x++) {
        a.label = tmplist[x];
        a.time = t * interval + x;
        a.value = fx[l][a.label][histgram[a.label].size()];
        Minlist[l].push_back(a);
      }
      //   if(1){
      int hist_max_label = In;
      int hist_maxlen = histgram[In].size();
      int delete_val = fx[l][In][1];  // 1番目の値
      int delete_label = In;

      int m = Minlist[l].size() - 1;

      int n = Minlist[l].size() - interval;

      while (m > n) {  //入ってきた部分の処理

        int label = Minlist[l][m].label;  //見ているMinlistのlabel

        if (Minlist[l][m].time != histgram[label][histgram[label].size() - 1]) {  //同じラベルのを消す(ヒストグラムの一番後ろに入ってきた時間と比べてる時間が違うなら消す)

          Minlist[l].erase(Minlist[l].begin() + m);

        } else {
          if (hist_maxlen < histgram[label].size()) {  //入ってきた部分で、histgramが最大のlabelを調べる
            hist_max_label = label;
          }

          if (Minlist[l][m].value > delete_val) {  //後ろが小さければ、前を消す
            Minlist[l].erase(Minlist[l].begin() + m);
          } else {
            if (fx[l][label][1] < delete_val) {  //後ろが大きいならhist_value更新
                                                 //  delete_val = fx[l][label][1];
              delete_label = In;
            }
          }
        }

        m--;
      }                                                   // While文の終わり
      int back_IN_num = 0;                                // 後方にあるhist_max_labelの要素数
      int pointer = histgram[hist_max_label].size() - 1;  //ヒストグラムの一番最後の時刻
      int hist_time = histgram[hist_max_label][pointer];  // = t
      delete_val = fx[l][delete_label][1];

      while (m >= 0) {  //元からの部分の処理

        int label = Minlist[l][m].label;  //見ているMinlistのlabel
        int h_size = histgram[label].size() - 1;
        if (Minlist[l][m].time != histgram[label][h_size]) {  //同じラベルのを消す(ヒストグラムの一番後ろに入ってきた時間と比べてる時間が違うなら消す)
          Minlist[l].erase(Minlist[l].begin() + m);
          same_count++;

        } else {
          while (Minlist[l][m].time < hist_time) {  //時刻によって判断
            back_IN_num++;
            int tmp = fx[l][hist_max_label][back_IN_num];
            // int delete_val =  fx[l][delete_label][back_IN_num];
            if (tmp < delete_val) {
              delete_val = tmp;
            }
            if (pointer > 0) {
              pointer--;
              hist_time = histgram[hist_max_label][pointer];
            } else {  //ヒストグラムの先頭まで行った
              hist_time = -1;
            }
          }

          int Minlist_value = Minlist[l][m].value;
          if (Minlist_value >= delete_val) {  //値を比べる

            Minlist[l].erase(Minlist[l].begin() + m);
            another_count++;
          }
        }

        m--;
      }

      a.label = In;
      a.time = t * interval + (interval - 1);
      a.value = in_value;
      Minlist[l].push_back(a);

      if (min_elem[l].value > in_value) {  //最小値の更新
        min_elem[l].value = in_value;
        min_elem[l].label = In;
      }
    }
    // Min_size = Min_size + Min_ave /r;
#ifdef DEBUG
    //   cout << min_elem[0].value << endl;
    if (t >= w) {
      vector<int> base_hash(num_of_hash);
      for (int l = 0; l < num_of_hash; l++) {
        int min = 100000;
        for (int i = t - w + 1; i <= t; i++) {
          int in = database[i];
          int value = fx[l][in][histgram[in].size()];
          if (min > value) {
            min = value;
          }
        }
        if (min_elem[l].value != min)
          cout << l << " " << min_elem[l].value << " " << min << endl;
      }
    }
#endif

    t++;
  }

  ave_length = sum_time_ave_length / t;
  cout << ave_length << "\n";

  cout << "same= " << same_count << " anohter= " << another_count << " out= " << out_count << "\n";
  // cout<<"\n";
  clock_t end = clock();  //ここまで時間測定
  cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
  return 0;
}

// int baseline[num_hash];
