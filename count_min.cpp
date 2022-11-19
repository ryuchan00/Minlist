#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class count_min {
  vector<vector<int>> m_count;

 public:
  vector<vector<int>> m_count_min_table;
  count_min(int c1, int c2);

  vector<vector<int>> count_min_table() const;
  int count(int i, int j);
  int get_freq(int j);
  int hash(int i, int j);
  void set_count(int j, int value);
  void add_count(int j, int value);
};

count_min::count_min(int c1, int c2) : m_count_min_table({}) {
  for (int i = 0; i < c1; i++) {
    vector<int> v;
    vector<int> count;
    for (int j = 0; j < c2; j++) {
      v.push_back(0);
      count.push_back(0);
    }
    // random_device get_rand_dev;
    // mt19937 get_rand_mt(get_rand_dev());  // seedに乱数を指定
    // shuffle(v.begin(), v.end(), get_rand_mt);
    m_count_min_table.push_back(v);
    m_count.push_back(count);
  }
}

vector<vector<int>> count_min::count_min_table() const {
  return m_count_min_table;
}

int count_min::count(int i, int j) {
  return m_count_min_table[i][hash(i, j)];
}

int count_min::get_freq(int j) {
  int min = 1000000000;
  for (int i = 0; i < m_count_min_table.size(); i++) {
    int freq = count(i, j);
    if (freq < min) {
      min = freq;
    }
  }
  return min;
}

int count_min::hash(int i, int j) {
  mt19937 get_rand_mt(i * m_count_min_table.size() + j);  // seedを固定
  return get_rand_mt() % m_count_min_table.size();
}

void count_min::set_count(int j, int value) {
  for (int i = 0; i < m_count_min_table.size(); i++) {
    m_count_min_table[i][hash(i, j)] = value;
  }
}

void count_min::add_count(int j, int value) {
  for (int i = 0; i < m_count_min_table.size(); i++) {
    int hash = count_min::hash(i, j);
    m_count_min_table[i][hash] = m_count_min_table[i][hash] + value;
  }
}

int get_freq(count_min &count_min, int j) {
  return count_min.get_freq(j);
}

void add_count(count_min &count_min, int j, int value) {
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