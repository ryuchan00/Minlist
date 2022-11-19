#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class histgram {
  vector<int> m_count;

 public:
  vector<int> m_histgram_table;
  histgram(int vm);

  vector<int> histgram_table() const;
  int count(int in);
  int get_freq(int in);
  void add_count(int in, int value);
};

histgram::histgram(int vm) : m_histgram_table({}) {
  for (int i = 0; i < vm; i++) {
    m_histgram_table.push_back(0);
  }
}

vector<int> histgram::histgram_table() const {
  return m_histgram_table;
}

int histgram::count(int in) {
  return m_histgram_table[in];
}

int histgram::get_freq(int in) {
  return m_histgram_table[in];
}

void histgram::add_count(int in, int value) {
  m_histgram_table[in] = m_histgram_table[in] + value;
}

int get_freq(histgram &histgram, int in) {
  return histgram.get_freq(in);
}

void add_count(histgram &histgram, int in, int value) {
  histgram.add_count(in, value);
}

// int main() {
//   int elements_num = 10;
//   histgram histgram(elements_num);
//   vector<int> a = histgram.histgram_table();
//   for (int i = 0; i < elements_num; i++) {
//       cout << a[i] << endl;
//   }
//   histgram.add_count(0, 10);
//   cout << histgram.m_histgram_table[0] << endl;
// }