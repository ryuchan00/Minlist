#include <deque>
#include <iostream>
#include <vector>

#include "contents.h"

int main(int argc, char *argv[]) {
  printf("size of (vector<int>)           : %ld\n", sizeof(std::vector<int>));
  printf("size of (vector<int>(1000))           : %ld\n", sizeof(std::vector<int>(1000)));
  printf("size of (vector<int> *))           : %ld\n", sizeof(std::vector<int> *));
  printf("size of (vector<deque<int>>)    : %ld\n", sizeof(std::vector<std::deque<int> >));
  printf("size of (deque<int>)    : %ld\n", sizeof(std::deque<int>));
  printf("size of int           : %ld\n", sizeof(int));
  printf("size of (int *)       : %ld\n", sizeof(int *));
  printf("size of (index)       : %ld\n", sizeof(index));
  return 0;
}