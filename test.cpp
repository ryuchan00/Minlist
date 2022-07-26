#include <array>  // ヘッダファイルインクルード

#include "contents.h"
#include "kyotsu.h"
#include "minhash.h"

using namespace std;

int main(int argc, char* argv[]) {
  std::array<std::array<int, 4>, 1> ar{};
  cout << ar.front();
  ar.front() = 11;  // 最初の要素を 11 に変更
  ar.back() = 44;   // 最後の要素を 44 に変更

  return 0;
}
