#include "contents.h"
#include "count_min_sketch.cpp"
#include "histgram.cpp"
#include "kyotsu.h"
#include "minhash.h"
using namespace std;

int main(int argc, char const *argv[]) {
  char *mhname;
  mhname = "test_minhash.txt";
  vector<int> minhash = read_line_minhash(mhname);
  for (int i = 0; i < minhash.size(); i++) {
    cout << minhash[i] << endl;
  }

  return 0;
}
