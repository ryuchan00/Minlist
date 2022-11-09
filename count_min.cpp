#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class count_min {
  vector<vector<int>> m_count_min_table;

 public:
  count_min(int c1, int c2);

  vector<vector<int>> count_min_table() const;
};

count_min::count_min(int c1, int c2) : m_count_min_table({}) {
  for (int i = 0; i < c2; i++) {
    vector<int> v;
    for (int j = 0; j < c1; j++) {
      v.push_back(j);
    }
    random_device get_rand_dev;
    mt19937 get_rand_mt(get_rand_dev());  // seedに乱数を指定
    shuffle(v.begin(), v.end(), get_rand_mt);
    m_count_min_table.push_back(v);
  }
}

vector<vector<int>> count_min::count_min_table() const {
  return m_count_min_table;
}

// int main() {
//   count_min table_a(10, 10);
//   vector<vector<int>> a = table_a.count_min_table();
//   for (int i = 0; i < 10; i++) {
//     for (int j = 0; j < 10; j++) {
//       cout << a[i][j] << " ";
//     }
//     cout << endl;
//   }
// }