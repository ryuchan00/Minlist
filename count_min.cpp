#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

#define PRIME 99991

class CountMinSketch {
  vector<vector<int>> m_count;

  // array of hash values for a particular item
  // contains two element arrays {aj,bj}
  int **hashes;

 public:
  vector<vector<int>> m_count_min_table;
  CountMinSketch(int c1, int c2);

  vector<vector<int>> count_min_table() const;
  int count(int i, int j);
  int get_freq(int j);
  int hash(int i, int j);
  void add_count(int j, int value);
  // generate "new" aj,bj
  void genajbj(int **hashes, int i);
};

CountMinSketch::CountMinSketch(int c1, int c2) : m_count_min_table({}) {
  for (int i = 0; i < c1; i++) {
    vector<int> v;
    vector<int> count;
    for (int j = 0; j < c2; j++) {
      v.push_back(0);
      count.push_back(0);
    }
    m_count_min_table.push_back(v);
    m_count.push_back(count);
  }

  // initialize d pairwise independent hashes
  srand(time(NULL));
  hashes = new int *[c1];
  for (int i = 0; i < c1; i++) {
    hashes[i] = new int[2];
    genajbj(hashes, i);
  }
}

// generates aj,bj from field Z_p for use in hashing
void CountMinSketch::genajbj(int **hashes, int i) {
  hashes[i][0] = int(float(rand()) * float(PRIME) / float(RAND_MAX) + 1);
  hashes[i][1] = int(float(rand()) * float(PRIME) / float(RAND_MAX) + 1);
}

vector<vector<int>> CountMinSketch::count_min_table() const {
  return m_count_min_table;
}

int CountMinSketch::count(int i, int j) {
  unsigned int hashval = 0;
  hashval = ((long)hashes[i][0] * j + hashes[i][1]) % PRIME % m_count_min_table[0].size();
  return m_count_min_table[i][hashval];
}

int CountMinSketch::get_freq(int j) {
  int min = 1000000000;
  for (int i = 0; i < m_count_min_table.size(); i++) {
    int freq = count(i, j);
    if (freq < min) {
      min = freq;
    }
  }
  return min;
}

void CountMinSketch::add_count(int j, int value) {
  unsigned int hashval = 0;

  for (int i = 0; i < m_count_min_table.size(); i++) {
    hashval = ((long)hashes[i][0] * j + hashes[i][1]) % PRIME % m_count_min_table[0].size();
    m_count_min_table[i][hashval] = m_count_min_table[i][hashval] + value;
  }
}

int get_freq(CountMinSketch &count_min, int j) {
  return count_min.get_freq(j);
}

void add_count(CountMinSketch &count_min, int j, int value) {
  count_min.add_count(j, value);
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