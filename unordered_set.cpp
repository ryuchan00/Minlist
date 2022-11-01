#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>

template <class C>
void print(const C& c, std::ostream& os = std::cout) {
  std::copy(std::begin(c), std::end(c), std::ostream_iterator<typename C::value_type>(os, ", "));
  os << std::endl;
}

int main() {
  std::unordered_set<std::string> us{
      "1st element",
      "2nd element",
      "3rd element",
  };

  print(us);

  us.emplace("4th element");

  print(us);

  us.erase("2nd element");

  print(us);

  std::cout << "----------" << std::endl;

  std::unordered_set<std::string> us2{
      "1st element",
      "2nd element",
      "3rd element",
  };

  print(us2);

  us2.emplace("4th element");

  print(us2);

  us2.erase("2nd element");

  print(us2);
}