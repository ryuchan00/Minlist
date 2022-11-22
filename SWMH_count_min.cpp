// PERFECT WINDOEWED COUNT MINを取り入れた手法で行う
//
/*Min Hashベースのマルチセットの近似解法*/
/*Active Indexを実装したもの*/

/*
 先行研究論文
 Xu, X., Gao, C., Pei, J., Wang, K., Al-Barakati, A.: Continuous similarity
 search for evolving queries. Knowl. Inf. Syst. 48(3), 649–678 (2016)
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ./MHI4 database.txt queri.txt シード値　SWの数　Minhash.txt マルチセットの上限 出力ファイル名//
// 元データの要素をランダムに組み合わせてデータベースを作る関数                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#include <algorithm>
#include <array>

#include "contents.h"
#include "count_min.cpp"
#include "histgram.cpp"
#include "kyotsu.h"
#include "minhash.h"

// #define DEBUG

#define PERIOD (100000)
using namespace std;

int main(int argc, char *argv[]) {
  int t = 0;

  vector<int> database;                  // データベース
  char *dbname = argv[1];                // database.txt
  database = readdatabase_line(dbname);  // データベース作成

  /*パラメータ*/
  int w = atoi(argv[2]);  // ウインドウサイズ
  int dmax = PERIOD + w;  // ストリームデータの長さ

  vector<vector<int>> minhash;
  vector<int>::iterator it;

  char *mhname = argv[3];            // Minhash.txt
  minhash = readminhash(mhname);     // ハッシュ関数の読み込み
  int num_of_hash = minhash.size();  // ハッシュ関数の数
  int vmw = minhash[0].size();       // 要素種類数 × 多重度の数
  int multi = atoi(argv[4]);         // wの中の要素の数の上限
  int vm = vmw / multi;              // 要素の種類数
  int search_limit = atoi(argv[5]);  // delete_val探索時の探索回数

  ////////////////////////////////////////////////////////////////
  /*Min-hashに用いるランダムの値のテーブル*/

  vector<vector<vector<index>>> fx(num_of_hash);
  fx = active_index(num_of_hash, vm, multi, minhash);

  ////////////////////////////////////////////////////////////////

  /*残っている要素のリストとスライディングウインドウに含まれている数のヒストグラムの作成*/

  vector<vector<contents>> Minlist(num_of_hash);  // 残っている要素のリスト[ハッシュ関数][残ってる要素]
  vector<std::array<int, 2>> ar(vm, {-1, -1});    // 固定長で試してみる
  vector<int> reset_count(num_of_hash, 0);

  int In;  //データストリームに入ってくる一番新しい要素
  // 最小値
  struct contents a;
  a.label = 99999;
  a.value = 5000000;
  vector<contents> min_elem(num_of_hash, a);

  int same_count = 0;
  int another_count = 0;
  int out_count = 0;

  ////////////////////////////////////////////////////////////////

  int c1 = 16;
  int c2 = 20;
  /*COUNT-MIN用のテーブルを作成する*/
  // CountMinSketch frequency_object(c1, c2);

  histgram frequency_object(vm);

  // ここから時刻による更新

  double ave_length, time_ave_length, sum_time_ave_length = 0.0;

  vector<vector<int>> allocation_pointer(num_of_hash, vector<int>(vm, 0));
  int tmp_pointer;
  clock_t start = clock();  // ここから時間を測る

  while (t < dmax) {
    // 出ていく処理
    if (t >= w) {
      int out = database[t - w];
      add_count(frequency_object, out, -1);
      int frequency = get_freq(frequency_object, out);
      if (ar[out][0] == (t - w)) {
        ar[out][0] = ar[out][1];
        ar[out][1] = -1;
      }
      double sum_length = 0;
      for (int l = 0; l < num_of_hash; l++) {
        // allocation_pointerを移動する
        if (fx[l][out][allocation_pointer[l][out]].multiplicity > frequency) {
          while (fx[l][out][allocation_pointer[l][out]].multiplicity > frequency) {
            // 不連続を考慮する
            allocation_pointer[l][out] -= 1;
            if (allocation_pointer[l][out] < 0) {
              allocation_pointer[l][out] = 0;
              break;
            }
          }
        }
        sum_length += Minlist[l].size();
        if (Minlist[l][0].time == t - w) {
          Minlist[l].erase(Minlist[l].begin());
          out_count++;
        }
        if (out == min_elem[l].label) {
          for (int m = 0; m < Minlist[l].size(); m++) {
            // COUNT-MINにより不連続になってしまった頻度のため，Minlistの補正作業を行う
            if (Minlist[l][m].value < fx[l][out][allocation_pointer[l][out]].value) {
              Minlist[l][m].value = fx[l][out][allocation_pointer[l][out]].value;
            }
          }

          // 最小値と同じラベルがストリームデータから出ていく時
          int min = 5000000;
          int m_label;

          for (int m = 0; m < Minlist[l].size(); m++) {
            int Minlist_value = Minlist[l][m].value;

            if (min > Minlist_value) {
              // 最小値を調べる
              int label = Minlist[l][m].label;
              int value_check = fx[l][label][allocation_pointer[l][label]].value;

              if (Minlist_value == value_check) {
                // 割り当て値に間違いがない場合
                min = Minlist_value;
                m_label = label;
              } else {
                Minlist[l][m].value = value_check;
                if (min > value_check) {
                  // 割り当て値が間違っている場合
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
    add_count(frequency_object, In, 1);
    int frequency = get_freq(frequency_object, In);

    for (int l = 0; l < num_of_hash; l++) {
      // allocation_pointerの次の要素が存在しているか確認している
      if (allocation_pointer[l][In] + 1 < fx[l][In].size() && fx[l][In][allocation_pointer[l][In] + 1].multiplicity <= frequency) {
        while (fx[l][In][allocation_pointer[l][In] + 1].multiplicity < frequency) {
          // 不連続を考慮する
          allocation_pointer[l][In] += 1;
          if (allocation_pointer[l][In] + 1 >= fx[l][In].size()) {
            allocation_pointer[l][In] = fx[l][In].size() - 1;
            break;
          }
        }
      }
      int in_value = fx[l][In][allocation_pointer[l][In]].value;  // 現在入ってきた要素の値
      int delete_val = 0;                                         // 1番目の値
      int m = Minlist[l].size() - 1;
      int back_IN_num = 0;  // 後方にあるhist_max_labelの要素数
      tmp_pointer = 0;      // delete_val算出のためのpointer
      int pointer = 0;
      int hist_time = t;

      while (m >= 0) {
        // Minlistのスキャン
        if (Minlist[l][m].label == In) {
          // 同じラベルのを消す
          Minlist[l].erase(Minlist[l].begin() + m);
          same_count++;
        } else {
          // back_IN_num=1のして初期化して、むだなwhileを省く
          while (Minlist[l][m].time < hist_time) {
            // 時刻によって判断
            back_IN_num++;
            if (fx[l][In][tmp_pointer].multiplicity < back_IN_num) {
              tmp_pointer += 1;
            }
            delete_val = fx[l][In][tmp_pointer].value;

            // back_IN_num=2のとき、hist_timeの更新はこれ以上必要ない。
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
            // 値を比べる
            Minlist[l].erase(Minlist[l].begin() + m);
            another_count++;
          }
        }
        m--;
      }
      a.label = In;
      a.time = t;
      a.value = in_value;
      a.multiplicity = frequency;
      Minlist[l].push_back(a);

      if (min_elem[l].value > in_value) {
        // 最小値の更新
        min_elem[l].value = in_value;
        min_elem[l].label = In;
        min_elem[l].multiplicity = frequency;
      }
    }

    ar[In][0] = t;
    t++;
  }

  ave_length = sum_time_ave_length / t;
  cout << ave_length << "\n";

  cout << "same= " << same_count << " anohter= " << another_count << " out= " << out_count << "\n";
  clock_t end = clock();  // ここまで時間測定
  cout << (double)(end - start) / CLOCKS_PER_SEC << " sec" << endl;
  struct rusage resource;
  getrusage(RUSAGE_SELF, &resource);
  printf("memory: %ld\n", resource.ru_maxrss);
  return 0;
}
