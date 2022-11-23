#include "count_min_sketch.cpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
using namespace std;

// run basic tests on CountMinSketch
int main(int argc, char **argv) {
  // Count for ar_str[i] is i1+i2+...
  // where i's are the positions where ar_str[i] occurs
  const char *ar_str[] = {
      "hello", "some", "one", "hello", "alice",
      "one", "lady", "let", "us", "lady",
      "alice", "in", "wonderland", "us", "lady",
      "lady", "some", "hello", "none", "pie"};

  CountMinSketch c(0.01, 0.1);
  unsigned int i, total = 0;
  map<const char *, int> mapitems;
  map<const char *, int>::const_iterator it;

  for (i = 0; i < 15; i++) {
    if ((it = mapitems.find(ar_str[i])) != mapitems.end()) {
      mapitems[ar_str[i]] += i;
    } else {
      mapitems[ar_str[i]] = i;
    }
    c.update(ar_str[i], i);
    total += i;
  }

  // 1. test for items in ar_str
  // note: since probablistic (and not deterministic)
  // might not be accurate sometimes
  for (it = mapitems.begin(); it != mapitems.end(); it++) {
    if (c.estimate(it->first) != mapitems[it->first]) {
      cout << "Incorrect count for " << it->first << ";error: " << abs(int(c.estimate(it->first) - mapitems[it->first]))
           << endl;
    } else {
      cout << "Correct count for '" << it->first << "' ;count: " << c.estimate(it->first) << endl;
    }
  }
  cout << "c.totalcount()==total? "
       << (c.totalcount() == total ? "True" : "False")
       << "Sketch Total: " << c.totalcount() << endl;

  // 2. test for items not in ar_str
  cout << "Testing for strings not in ar_str..." << endl;
  cout << c.estimate("blabla") << endl;
  cout << c.estimate("yoyo!") << endl;
  cout << c.estimate("hello") << endl;

  return 0;
}
