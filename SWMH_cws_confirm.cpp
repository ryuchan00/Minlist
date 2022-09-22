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

#include <sys/time.h>

#include <algorithm>
#include <array>
#include <cstdlib>

#include "contents.h"
#include "kyotsu.h"
#include "minhash.h"

#define DEBUG

#define PERIOD (100000)
#define MAX (1000000000)
using namespace std;

// ハッシュテーブルを線形探索して、ある時点tのスライドウィンドゥの中に存在する最初のハッシュ値が見つかった場合に探索回数を返す。
// c: スライドウィンドゥ内の要素をハッシュ値に変換したもの
// hash_table1: 要素のハッシュテーブル
// hash_table2: 多重度のハッシュテーブル

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
  struct timeval tv;                                                // 変数の宣言
  gettimeofday(&tv, NULL);                                          // 現在の時刻を取得
  srand((unsigned int)tv.tv_sec * ((unsigned int)tv.tv_usec + 1));  // 秒×μ秒 + 1
  // srand((int)time(NULL));
  int sample_t1 = rand() % dmax;
  int sample_t2 = rand() % dmax;
  vector<vector<int>> sampled_hash_list_t1(num_of_hash);
  vector<vector<int>> sampled_hash_list_t2(num_of_hash);
  vector<int> in_t1;
  vector<int> in_t2;
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
  vector<vector<int>> fx_b(num_of_hash, vector<int>(multi + 1, MAX));

  for (int l = 0; l < num_of_hash; l++) {
    for (int s = 1; s <= multi; s++) {
      int Allocation_s = minhash[l][(multi + (s - 1))];  //アルファベットに対してs番目の割り当て値
                                                         // if (Allocation_s > fx_b[l][s - 1]) {
      // fx_b[l][s] = fx_b[l][s - 1];
      // } else {
      fx_b[l][s] = Allocation_s;
      // }
    }
  }

  ////////////////////////////////////////////////////////////////
#ifdef DEBUG
  // 近似Jaccard係数をハッシュ関数の数だけ求めてみる
  double match_count = 0.0;

  in_t1 = {1, 2, 2, 2};
  // in_t1 = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
  // in_t2 = {1, 1, 2, 2, 2, 3, 4};
  std::vector<int> histgram_mh(2, 0);

  for (int i; i < num_of_hash; i++) {
    histgram_mh[mh(in_t1, fx_a[i], fx_b[i]) - 1] += 1;
    // if (mh(in_t1, fx_a[i], fx_b[i]) == mh(in_t2, fx_a[i], fx_b[i])) {
    // match_count += 1;
    // }
  }
  for (int i = 0; i < 2; i++) {
    cout << "value:" << i << endl;
    cout << "count:" << histgram_mh[i] << endl;
  }
  cout << "ハッシュ関数の数: " << num_of_hash << endl;
  // cout << "近似jaccard係数: " << match_count / num_of_hash << endl;

  // 厳密なJaccard係数を求める
  // cout << "厳密なjaccard係数: " << strict_jaccard(in_t1, in_t2) << endl;
#endif
  return 0;
}
