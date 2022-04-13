#include "syntax.hpp"
// const OPP mutable

int main() {
#if 0
  std::cout << std::boolalpha;

  // any type
  std::any a = 1;
  std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
  a = 3.14;
  std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
  a = true;
  std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
  a = "Jiao";
  std::cout << a.type().name() << ": " << std::any_cast<const char*>(a) << '\n';
  // std::cout << a.type().name() << ": " << std::any_cast<std::string&>(a) << '\n';  // error
  // std::string& name = std::any_cast<std::string&>(a);  // error
  std::string str = "Jiao";
  a = str;
  std::cout << a.type().name() << ": " << std::any_cast<std::string>(a) << '\n';

  // bad cast
  try
  {
    a = 1;
    std::cout << std::any_cast<float>(a) << '\n';
  }
  catch (const std::bad_any_cast &e)
  {
    std::cout << e.what() << '\n';
  }

  // has value
  a = 1;
  if (a.has_value())
  {
    std::cout << a.type().name() << '\n';
  }

  // reset
  a.reset();
  if (!a.has_value())
  {
    std::cout << "no value\n";
  }

  // pointer to contained data
  a = 1;
  int *i = std::any_cast<int>(&a);
  std::cout << *i << "\n";
#endif
  // std::unordered_set<int> uni;  // only have a key and it most be unique
  // std::set<int> uni;  // same to unordered_set but sorted
  // std::unordered_map<int, int> uni;  // {key, value}
  std::map<int, std::string> uni;  // {key, value}  sorted by key AND the key is unique
  uni.insert({1, "jiao"});
  // uni.insert({1, 3});
  // uni.insert({2, 1});
  uni.insert({3, "jie"});
  // for (auto i : uni) {
  //   // std::cout << i << std::endl;
  //   std::cout << i.first << ',' << i.second << std::endl;
  // }
  // auto it = uni.find("jiao");  // run error, it's just can find key
  auto it = uni.find(1);
  if (it != uni.end()) {
    std::cout << it->first << ',' << it->second << std::endl;
  } else {
    std::cout << "Not found!\n";
  }
  return 0;
}
