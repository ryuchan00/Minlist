#include "contents.h"
#include "count_min_sketch.cpp"
#include "histgram.cpp"
#include "kyotsu.h"
#include "minhash.h"
using namespace std;

void read_line_minhash() {
  cout << "read_line_minhash" << endl;
  char *mhname;
  mhname = "test_minhash.txt";
  vector<int> minhash = read_line_minhash(mhname);
  for (int i = 0; i < minhash.size(); i++) {
    cout << minhash[i] << endl;
  }
}

void line_of_active_index() {
  cout << "line_of_active_index" << endl;
  int vm = 2;
  int multi = 2;
  vector<int> minhash = {4, 1, 3, 2};
  vector<vector<index>> active_index = line_of_active_index(vm, multi, minhash);
  for (int i = 0; i < active_index.size(); i++) {
    for (int j = 0; j < active_index[i].size(); j++) {
      cout << "(" << active_index[i][j].multiplicity << "," << active_index[i][j].value << "),";
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  read_line_minhash();
  line_of_active_index();

  return 0;
}
