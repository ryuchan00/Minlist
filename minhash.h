#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <set>
#include <sstream>
#include <vector>

#include "count_min_sketch.cpp"
#include "histgram.cpp"
// #include "count_min_sketch.cpp"
// #include "histgram.cpp"
// #include "count_min_sketch.hpp"

/*Minhash読み込み*/
std::vector<std::vector<int>> readminhash(char *filename) {
  int i = 0;
  std::vector<std::vector<int>> minhash;
  std::ifstream ifs(filename);
  int line = 0;
  std::vector<int> empty;
  std::string str, x;
  while (getline(ifs, str)) {
    std::istringstream line(str);
    minhash.push_back(empty);
    while (getline(line, x, ',')) {
      minhash[i].push_back(atoi(x.c_str()));
    }
    i++;
  }
  return minhash;
}

/*Minhashの1行のみ読み込み*/
std::vector<int> read_line_minhash(char *filename) {
  std::vector<int> minhash;
  std::ifstream ifs(filename);
  std::vector<int> empty;
  std::string str, x;
  getline(ifs, str);
  std::istringstream line(str);
  while (getline(line, x, ',')) {
    minhash.push_back(atoi(x.c_str()));
  }
  return minhash;
}

/*ハッシュ値の計算*/
int hashvalue(std::vector<int> &hash, std::vector<int> &data) {
  int value = hash.size() + 1;
  for (int i = 0; i < data.size(); i++) {
    if (value > hash[data[i]]) {
      value = hash[data[i]];
    }
  }
  return value;
}

// 厳密なJaccard係数の算出
double strict_jaccard(std::vector<int> &set_a, std::vector<int> &set_b) {
  std::vector<int> intersection_in;
  std::vector<int> union_in;
  sort(set_a.begin(), set_a.end());
  sort(set_b.begin(), set_b.end());

  // aとbの積集合を得る
  set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), back_inserter(intersection_in));

  // aとbの和集合を作る
  set_union(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), inserter(union_in, std::end(union_in)));

  return (double)intersection_in.size() / union_in.size();
}

// 近似Jaccard係数の算出
int mh(std::vector<int> &s, std::vector<std::vector<int>> &fx) {
  int vm = fx.size();
  std::vector<int> histgram(vm, 0);
  int min = std::numeric_limits<int>::max();
  int min_s_i;

  for (int i = 0; i < s.size(); i++) {
    histgram[s[i]] += 1;
    int in_value = fx[s[i]][histgram[s[i]]];
    if (in_value < min) {
      min = in_value;
      min_s_i = s[i];
    }
  }
  return min_s_i;
}

// cwsの近似Jaccard係数の算出
int cws_mh(std::vector<int> &s, std::vector<int> &fx_a, std::vector<int> &fx_b) {
  int vm = fx_a.size();
  std::vector<int> histgram(vm, 0);
  int min = std::numeric_limits<int>::max();
  int min_s_i;

  for (int i = 0; i < s.size(); i++) {
    histgram[s[i]] += 1;
    int in_value = fx_a[s[i]] + fx_b[histgram[s[i]]];
    if (in_value < min) {
      min = in_value;
      min_s_i = s[i];
    }
  }
  return min_s_i;
}

// active_indexの近似Jaccard係数の算出
int active_index_mh(std::vector<int> &s, std::vector<std::vector<index>> &fx) {
  int vm = fx.size();
  std::vector<int> histgram(vm, 0);
  int min = std::numeric_limits<int>::max();
  int min_s_i;
  std::vector<int> pointer(vm, 0);

  for (int i = 0; i < s.size(); i++) {
    int in = s[i];
    histgram[in] += 1;
    if (pointer[in] + 1 < fx[in].size() && fx[in][pointer[in] + 1].multiplicity == histgram[in]) {
      pointer[in] += 1;
    }

    int in_value = fx[in][pointer[in]].value;
    if (in_value < min) {
      min = in_value;
      min_s_i = s[i];
    }
  }
  return min_s_i;
}

// count-minの組み合わせの近似Jaccard係数の算出
int count_min_mh(std::vector<int> &stream_data, std::vector<std::vector<int>> &fx, int &c1, int &c2) {
  CountMinSketch *frequency_object = new CountMinSketch(c1, c2);
  // Histgram *frequency_object = new Histgram(stream_data.size());
  int min_allocation_num = std::numeric_limits<int>::max();
  int min_s_i;
  int frequency;
  int in_value;

  for (int i = 0; i < stream_data.size(); i++) {
    int in = stream_data[i];
    update(frequency_object, in, 1);
    frequency = get_freq(frequency_object, in);

    in_value = fx[in][frequency];
    if (in_value < min_allocation_num) {
      min_allocation_num = in_value;
      min_s_i = stream_data[i];
    }
  }
  return min_s_i;
}

std::vector<std::vector<std::vector<index>>> active_index(int &num_of_hash, int &vm, int &multi, std::vector<std::vector<int>> &minhash) {
  std::vector<std::vector<std::vector<index>>> fx(num_of_hash, std::vector<std::vector<index>>(vm, std::vector<index>()));
  for (int l = 0; l < num_of_hash; l++) {
    for (int i = 0; i < vm; i++) {
      int before_value = std::numeric_limits<int>::max();
      for (int s = 1; s <= multi; s++) {
        int Allocation_s = minhash[l][i + (vm * (s - 1))];  // アルファベットに対してs番目の割り当て値
        if (!(Allocation_s > before_value)) {
          struct index idx;
          idx.multiplicity = s;
          idx.value = Allocation_s;
          fx[l][i].push_back(idx);
          before_value = Allocation_s;
        }
      }
    }
  }
  return fx;
}

std::vector<std::vector<index>> line_of_active_index(int &vm, int &multi, std::vector<int> &minhash) {
  std::vector<std::vector<index>> fx(std::vector<std::vector<index>>(vm, std::vector<index>()));
  for (int i = 0; i < vm; i++) {
    int before_value = std::numeric_limits<int>::max();
    for (int s = 1; s <= multi; s++) {
      int Allocation_s = minhash[i + (vm * (s - 1))];  // アルファベットに対してs番目の割り当て値
      if (!(Allocation_s > before_value)) {
        struct index idx;
        idx.multiplicity = s;
        idx.value = Allocation_s;
        fx[i].push_back(idx);
        before_value = Allocation_s;
      }
    }
  }
  return fx;
}