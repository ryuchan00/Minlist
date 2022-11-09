#include <iostream>
#include <random>

int main() {
  std::random_device seed_gen;
  std::mt19937 engine(2);

  for (int i = 0; i < 10; ++i) {
    std::uint32_t result = engine();
    std::cout << result << std::endl;
  }
}