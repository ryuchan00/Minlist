#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

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

/*
struct rank
{
        int id;
        int sim;
        bool operator<(const rank& rhs) const
        {
                return sim > rhs.sim;
        }
        };*/
// jac.hとほぼ同じ。
// simがintになっているのは、
//ハッシュの衝突回数で類似度
//を近似してるから

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
  int min = 999999;
  int min_si;

  for (int i = 0; i < s.size(); i++) {
    histgram[s[i]] += 1;
    int in_value = fx[s[i]][histgram[s[i]]];
    if (in_value < min) {
      min = in_value;
      min_si = s[i];
    }
  }
  return min_si;
}

// cwsの近似Jaccard係数の算出
int cws_mh(std::vector<int> &s, std::vector<int> &fx_a, std::vector<int> &fx_b) {
  int vm = fx_a.size();
  std::vector<int> histgram(vm, 0);
  int min = 999999;
  int min_si;

  for (int i = 0; i < s.size(); i++) {
    histgram[s[i]] += 1;
    int in_value = fx_a[s[i]] + fx_b[histgram[s[i]]];
    if (in_value < min) {
      min = in_value;
      min_si = s[i];
    }
  }
  return min_si;
}

// active_indexの近似Jaccard係数の算出
int active_index_mh(std::vector<int> &s, std::vector<std::vector<index>> &fx) {
  int vm = fx.size();
  std::vector<int> histgram(vm, 0);
  int min = 999999;
  int min_si;
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
      min_si = s[i];
    }
  }
  return min_si;
}

std::vector<std::vector<std::vector<index>>> active_index(int &num_of_hash, int &vm, int &multi, std::vector<std::vector<int>> &minhash) {
  std::vector<std::vector<std::vector<index>>> fx(num_of_hash, std::vector<std::vector<index>>(vm, std::vector<index>()));
  for (int l = 0; l < num_of_hash; l++) {
    for (int i = 0; i < vm; i++) {
      int before_value = 500000000;
      for (int s = 1; s <= multi; s++) {
        int Allocation_s = minhash[l][i + (vm * (s - 1))];  //アルファベットに対してs番目の割り当て値
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