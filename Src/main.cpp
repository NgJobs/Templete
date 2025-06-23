#include "main.h"

#include <iostream>

#include "sum.h"

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::cout << PI << std::endl << sum(1, 2) << std::endl;
  for (int i = 0; i < 10; ++i) {
    std::cout << "Counter: " << i << std::endl;
  }
  return 0;
}
