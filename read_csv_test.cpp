/*
  stdio.h [fgetc]

  書式: int fgetc(FILE *fp)
  機能: ファイルから 1 文字ずつ読み込む
  引数: FILE *fp: ファイル (ストリーム) ポインタ
  戻り値: 成功すると, 読み込んだ 1 文字を返し,
          ファイル終端の場合は, EOF (-1) を返す.
*/

#include <stdio.h>

#include <iostream>
#include <string>  // ヘッダファイルインクルード
#include <vector>
using namespace std;  //  名前空間指定

int main(void) {
  FILE *fp;
  char *fname = "test1.csv";
  int c;
  string str;  // ローカル変数として、str を生成

  fp = fopen(fname, "r");
  if (fp == NULL) {
    printf("%s ファイルが開けない\n", fname);
    return -1;
  }

  printf("--fgetc--\n");
  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      break;
    }
    // printf("in %c ", c);
    if (c == ',') {
      cout << str << endl;
      str = "";
      // printf("%c ", str);
      continue;
    }
    str.push_back(c);
  }
  if (str.size() > 0) {
    cout << str << endl;
  }

  fclose(fp);

  std::vector<int> v{1, 2, 3, 4};
  // v に要素を格納;
  auto itr = v.begin();  // 最初の要素を指すイテレータ
  cout << *itr << endl;

  return 0;
}
