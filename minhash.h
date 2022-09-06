#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

/*Minhash読み込み*/
std::vector<std::vector<int> > readminhash(char *filename) {
  int i = 0;
  std::vector<std::vector<int> > minhash;
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
double strict_jaccard(std::vector<int> set_a, std::vector<int> set_b) {
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
int mh(std::vector<int> &s, std::vector<int> &fx_a, std::vector<int> &fx_b) {
  int vm = fx_a.size();
  std::vector<int> histgram(vm, 0);
  int min = 999999;

  for (int i = 0; i < s.size(); i++) {
    histgram[s[i]] += 1;
    int in_value = fx_a[s[i]] + fx_b[histgram[s[i]]] * vm;
    if (in_value < min) {
      min = in_value;
    }
  }
  return min;
}