#include "contents.h"
#include "minhash.h"

using namespace std;

int main(int argc, char *argv[]) {
  vector<vector<int>> minhash;
  minhash.push_back({4, 5, 6, 7, 3, 11, 8, 9});

  int num_of_hash = minhash.size();
  int multi = 4;
  int vm = minhash[0].size() / multi;

  vector<vector<vector<index>>> fx(num_of_hash, vector<vector<index>>(vm, vector<index>()));

  // minhash[1] = {4, 3, 2, 1, 5, 6, 7, 8};
  fx = active_index(num_of_hash, vm, multi, minhash);

  for (int i = 0; i < num_of_hash; i++) {
    for (int j = 0; j < vm; j++) {
      // cout << fx[i][j].size() << endl;
      for (int k = 0; k < fx[i][j].size(); k++) {
        cout << "[" << fx[i][j][k].multiplicity << "," << fx[i][j][k].value << "]";
      }
      cout << endl;
    }
  }
}