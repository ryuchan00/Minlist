// Count-Minの正確性を計測する
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#include <algorithm>
#include <array>

#include "contents.h"
// #include "count_min_sketch.cpp"
#include "kyotsu.h"
#include "minhash.h"

#define DEBUG
#define STREAM_DATA
#define PERIOD (100000)
using namespace std;

int main(int argc, char *argv[]) {
  int t = 0;

  /*パラメータ*/
  int w = atoi(argv[3]);  // ウインドウサイズ

  vector<int> database_raw;                  // データベース
  char *dbname = argv[1];                    // database.txt
  database_raw = readdatabase_line(dbname);  // データベース作成
  vector<int> database{database_raw.begin(), database_raw.begin() + w};
  std::sort(database.begin(), database.end(), std::greater<int>());
#ifdef DEBUG
  cout << database.size() << endl;
#endif

  vector<int> database2_raw;                   // 近似を計測するための別のデータベース
  char *dbname2 = argv[2];                     // database.txt
  database2_raw = readdatabase_line(dbname2);  // データベース作成
  vector<int> database2{database2_raw.begin(), database2_raw.begin() + w};
  std::sort(database2.begin(), database2.end(), std::greater<int>());

#ifdef DEBUG
  cout << database2.size() << endl;
#endif

  vector<vector<int>> minhash;

  char *mhname = argv[4];              // Minhash.txt
  minhash = readminhash(mhname);       // ハッシュ関数の読み込み
  int num_of_hash = minhash.size();    // ハッシュ関数の数
  int multi = atoi(argv[5]);           // wの中の要素の数の上限
  int vm = minhash[0].size() - multi;  // 要素の種類数
  int vmw = vm * multi;                // 要素種類数 × 多重度の数

  #ifdef DEBUG
    for (int i = 0; i < 100; i++) {
      cout << database[i] << " " << database2[i] << endl;
    }
  #endif

  vector<vector<vector<int>>> fx(num_of_hash, vector<vector<int>>(vm, vector<int>(multi + 1, numeric_limits<int>::max())));

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

  int c1 = atoi(argv[6]);
  int c2 = atoi(argv[7]);
  // 近似Jaccard係数をハッシュ関数の数だけ求めてみる
  double match_count = 0.0;
  double match_count2 = 0.0;

  for (int i = 0; i < num_of_hash; i++) {
    if (count_min_mh(database, fx[i], c1, c2) == count_min_mh(database2, fx[i], c1, c2)) {
      match_count += 1;
    }
    if (mh(database, fx[i]) == mh(database2, fx[i])) {
      match_count2 += 1;
    }
  }
  cout << "CountMinSketchを用いた近似jaccard係数: " << match_count / num_of_hash << endl;
  cout << "MinHashを用いた近似jaccard係数: " << match_count2 / num_of_hash << endl;

  // 厳密なJaccard係数を求める
  cout << "厳密なjaccard係数: " << strict_jaccard(database, database2) << endl;

  return 0;
}
