#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<std::string, bool>> bra;

int main() {
  bra.push_back(std::make_pair("jiao", true));
  bra.push_back(std::make_pair("shi", false));
  std::cout << bra.back().first << std::endl;
  return 0;
}
