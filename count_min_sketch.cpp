// #include "count_min_sketch.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;

#define PRIME 99991
#define MIN(a, b) (a < b ? a : b)

class CountMinSketch {
  // array of hash values for a particular item
  // contains two element arrays {aj,bj}
  int **hashes;
  unsigned int c1, c2;
  // array of arrays of counters
  int **countMinSketchTable;
  // vector<vector<int>> countMinSketchTable;

 public:
  CountMinSketch(int c1, int c2);

  int get_freq(int j);
  void update(int j, int c);
  // generate "new" aj,bj
  void genajbj(int **hashes, int i);

  // destructor
  ~CountMinSketch();
};

CountMinSketch::CountMinSketch(int in_c1, int in_c2) {
  c1 = in_c1;
  c2 = in_c2;
  // initialize counter array of arrays, countMinSketchTable
  countMinSketchTable = new int *[c1];
  unsigned int i, j;
  for (i = 0; i < c1; i++) {
    countMinSketchTable[i] = new int[c2];
    for (j = 0; j < c2; j++) {
      countMinSketchTable[i][j] = 0;
    }
  }

  // initialize c1 pairwise independent hashes
  srand(time(NULL));
  hashes = new int *[c1];
  for (int i = 0; i < c1; i++) {
    hashes[i] = new int[2];
    genajbj(hashes, i);
  }
}

// CountMinSkectch destructor
CountMinSketch::~CountMinSketch() {
  // free array of counters, C
  unsigned int i;
  for (i = 0; i < c1; i++) {
    delete[] countMinSketchTable[i];
  }
  delete[] countMinSketchTable;

  // free array of hash values
  for (i = 0; i < c1; i++) {
    delete[] hashes[i];
  }
  delete[] hashes;
}

// generates aj,bj from field Z_p for use in hashing
void CountMinSketch::genajbj(int **hashes, int i) {
  hashes[i][0] = int(float(rand()) * float(PRIME) / float(RAND_MAX) + 1);
  hashes[i][1] = int(float(rand()) * float(PRIME) / float(RAND_MAX) + 1);
}

int CountMinSketch::get_freq(int j) {
  int minval = numeric_limits<int>::max();
  unsigned int hashval = 0;
  for (unsigned int i = 0; i < c1; i++) {
    hashval = ((int)hashes[i][0] * j + hashes[i][1]) % PRIME % c2;
    minval = MIN(minval, countMinSketchTable[i][hashval]);
  }
  return minval;
}

// countMinSketch update j count (int)
void CountMinSketch::update(int j, int c) {
  unsigned int hashval = 0;
  for (unsigned int i = 0; i < c1; i++) {
    hashval = ((int)hashes[i][0] * j + hashes[i][1]) % PRIME % c2;
    countMinSketchTable[i][hashval] = countMinSketchTable[i][hashval] + c;
  }
}

int get_freq(CountMinSketch *CountMinSketch, int j) {
  return CountMinSketch->get_freq(j);
}

void update(CountMinSketch *CountMinSketch, int j, int value) {
  CountMinSketch->update(j, value);
}

// 動作確認用のmain関数
// int main() {
//   count_min table_a(10, 10);
//   vector<vector<int>> a = table_a.count_min_table();
//   for (int i = 0; i < 10; i++) {
//     for (int j = 0; j < 10; j++) {
//       cout << a[i][j] << " ";
//     }
//     cout << endl;
//   }
//   cout << table_a.hash(1, 5) << endl;
//   table_a.set_count(0, 0, 10);
//   cout << table_a.count_min_table()[0][0] << endl;
// }