/*Min Hashベースのマルチセットの近似解法*/
// 割り当て値を除くスライディングウィンドウのみの基本的なメモリ使用量を計測するだけのプログラム

/*
 先行研究論文
 Xu, X., Gao, C., Pei, J., Wang, K., Al-Barakati, A.: Continuous similarity
 search for evolving queries. Knowl. Inf. Syst. 48(3), 649–678 (2016)
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ./MHI4 database.txt queri.txt シード値　SWの数　Minhash.txt マルチセットの上限 出力ファイル名//
// 元データの要素をランダムに組み合わせてデータベースを作る関数                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "contents.h"
#include "kyotsu.h"
#include "minhash.h"

//#define DEBUG

#define PERIOD (100000)
using namespace std;

int main(int argc, char* argv[]) {
  int t = 0;

  vector<int> database;                  //データベース
  char* dbname = argv[1];                // database.txt
  database = readdatabase_line(dbname);  //データベース作成
  // cout << database.size() << endl;

  /*パラメータ*/
  int w = atoi(argv[2]);  //ウインドウサイズ
  int dmax = PERIOD + w;  //ストリームデータの長さ

  ////////////////////////////////////////////////////////////////
  /*Min-hashに用いるランダムの値のテーブル*/

  ////////////////////////////////////////////////////////////////

  /*残っている要素のリストとスライディングウインドウに含まれている数のヒストグラムの作成*/

  int In;  //データストリームに入ってくる一番新しい要素

  clock_t start = clock();  //ここから時間を測る

  // cout << ave_length << "\n";

  // cout << "same= " << same_count << " anohter= " << another_count << " out= " << out_count << "\n";
  // cout<<"\n";
  clock_t end = clock();  //ここまで時間測定
  // cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
  return 0;
}

// int baseline[num_hash];
