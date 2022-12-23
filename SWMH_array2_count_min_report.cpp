// 配列を持つデータ構造array(2)を試してみる
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
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#include <algorithm>
#include <array>

#include "contents.h"
#include "kyotsu.h"
#include "minhash.h"

#define DEBUG

#define PERIOD (100000)
using namespace std;

int main(int argc, char *argv[]) {
  int t = 0;

  vector<int> database;                  // データベース
  char *dbname = argv[1];                // database.txt
  database = readdatabase_line(dbname);  // データベース作成

  vector<int> database2;                   // 近似を計測するための別のデータベース
  char *dbname2 = argv[5];                 // database.txt
  database2 = readdatabase_line(dbname2);  // データベース作成

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

  vector<vector<vector<int>>> fx(num_of_hash, vector<vector<int>>(vm, vector<int>(multi + 1, 5000000)));

  for (int l = 0; l < num_of_hash; l++) {
    for (int i = 0; i < vm; i++) {
      for (int s = 1; s <= multi; s++) {
        int Allocation_s = minhash[l][i + (vm * (s - 1))];  // アルファベットに対してs番目の割り当て値
        if (Allocation_s > fx[l][i][s - 1]) {
          fx[l][i][s] = fx[l][i][s - 1];
        } else {
          fx[l][i][s] = Allocation_s;
        }
      }
    }
  }

#ifdef DEBUG
  std::vector<int> in1(database.begin() + 1, database.begin() + 100 + 1);
  std::vector<int> in2(database2.begin() + 1, database2.begin() + 100 + 1);

  // 近似Jaccard係数をハッシュ関数の数だけ求めてみる
  double match_count = 0.0;

  for (int i = 0; i < num_of_hash; i++) {
    if (mh(in1, fx[i]) == mh(in2, fx[i])) {
      match_count += 1;
    }
  }
  // cout << "近似jaccard係数: " << match_count / num_of_hash << endl;

  // 厳密なJaccard係数を求める
  // cout << "厳密なjaccard係数: " << strict_jaccard(in1, in2) << endl;

  int c1 = atoi(argv[6]);
  int c2 = atoi(argv[7]);
  // 近似Jaccard係数をハッシュ関数の数だけ求めてみる
  double match_count2 = 0.0;

  for (int i = 0; i < num_of_hash; i++) {
    if (count_min_mh(in1, fx[i], c1, c2) == count_min_mh(in2, fx[i], c1, c2)) {
      match_count2 += 1;
    }
  }
  // cout << "Count-Minのjaccard係数: " << match_count2 / num_of_hash << endl;

  // cout << "近似jaccard係数,厳密なjaccard係数,Count-Minのjaccard係数";
  cout << (match_count / num_of_hash) << "," << strict_jaccard(in1, in2) << "," << (match_count2 / num_of_hash) << endl;
#endif

  return 0;
}
