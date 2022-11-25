#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Histgram {
  int *histgramTable;

 public:
  Histgram(int vm);

  int get_freq(int in);
  void update(int in, int value);
};

Histgram::Histgram(int vm) {
  histgramTable = (int *)malloc(sizeof(int) * vm);

  // histgramTable = new int *[vm];
  for (int i = 0; i < vm; i++) {
    histgramTable[i] = 0;
  }
}

int Histgram::get_freq(int in) {
  return histgramTable[in];
}

void Histgram::update(int in, int value) {
  histgramTable[in] = histgramTable[in] + value;
}

int get_freq(Histgram *Histgram, int in) {
  return Histgram->get_freq(in);
}

void update(Histgram *Histgram, int in, int value) {
  Histgram->update(in, value);
}

// int main() {
//   int elements_num = 10;
//   histgram histgram(elements_num);
//   vector<int> a = histgram.histgram_table();
//   for (int i = 0; i < elements_num; i++) {
//       cout << a[i] << endl;
//   }
//   histgram.add_count(0, 10);
//   cout << histgram.histgramTable[0] << endl;
// }