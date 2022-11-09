#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  std::vector<int> vec(3, 0);
  vec = {1, 2, 3};
  std::random_device get_rand_dev;
  std::mt19937 get_rand_mt(get_rand_dev());  // seedに乱数を指定
  std::shuffle(vec.begin(), vec.end(), get_rand_mt);
  for (int i = 0; i < 3; i++) {
    cout << vec[i] << endl;
  }
}