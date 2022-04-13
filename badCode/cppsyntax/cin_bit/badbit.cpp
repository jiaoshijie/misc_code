#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void aboutfile();
void aboutstdio();
void aboutsync();
void badtry();

int main() {
  // aboutfile();
  // aboutstdio();
  // aboutsync();
  cout << "Enter Text: ";
  std::string str;
  cin >> str;
  while(getchar() != '\n');  // cin.sync() didn't work. TODO
  // if (cin.sync() == 0) {
  //   cout << "sync\n";
  // }
  cout << "Enter Number: ";
  int n;
  cin >> n;
  cout << "Enter Another Number: ";
  int n2;
  cin >> n2;
  cout << "You Entered: " << str << ", " << n << ", " << n2 << endl;
  return 0;
}

void badtry() {
  // https://cplusplus.com/reference/istream/istream/sync/?kw=sync
  // The result is not same thing with this site example.
  char first, second;

  std::cout << "Please, enter a word: ";
  first = std::cin.get();
  std::cin.sync();

  std::cout << "Please, enter another word: ";
  second = std::cin.get();

  std::cout << "The first word began by " << first << '\n';
  std::cout << "The second word began by " << second << '\n';
}

void file_abc()
{
    std::ofstream f("test.txt");
    f << "abc\n";
}

void file_123()
{
    std::ofstream f("test.txt");
    f << "123\n";
}

void aboutsync() {
    file_abc(); // file now contains "abc"
    std::ifstream f("test.txt");
    std::cout << "Reading from the file\n";
    char c;
    f >> c; std::cout << c;
    file_123(); // file now contains "123"
    f >> c; std::cout << c;
    f >> c; std::cout << c << '\n';
    f.close();

    file_abc(); // file now contains "abc"
    f.open("test.txt");
    std::cout << "Reading from the file, with sync()\n";
    f >> c; std::cout << c;
    file_123(); // file now contains "123"
    f.sync();
    f >> c; std::cout << c;
    f >> c; std::cout << c << '\n';
}

void aboutstdio() {
  // char str[20];
  // string s;
  int num;
  cout << cin.good() << endl;
  cout << cin.eof() << endl;
  cout << cin.fail() << endl;
  cout << cin.bad() << endl;
  // cin.getline(str, 20);
  // cin.ignore(1024, ' ');
  cin >> num;
  cout << cin.good() << endl;
  cout << cin.eof() << endl;
  cout << cin.fail() << endl;
  cout << cin.bad() << endl;
  // cin.clear();
  // cin >> s;
  // cout << s << endl;
}

void aboutfile() {
  char buffer[80];
  std::fstream myfile;
  myfile.open("main.txt", std::fstream::in);

  myfile << "test";
  if (myfile.fail()) {
    cout << myfile.good() << endl;
    cout << myfile.fail() << endl;
    cout << myfile.bad() << endl;
    cout << myfile.eof() << endl;
    myfile.clear();
  }
  cout << myfile.good() << endl;
  cout << myfile.fail() << endl;
  cout << myfile.bad() << endl;
  cout << myfile.eof() << endl;
  myfile.ignore(1024, ' ');
  myfile.getline(buffer, 80);
  cout << myfile.good() << endl;
  cout << myfile.fail() << endl;
  cout << myfile.bad() << endl;
  cout << myfile.eof() << endl;
  cout << buffer << endl;
  myfile.getline(buffer, 80);
  cout << myfile.good() << endl;
  cout << myfile.fail() << endl;
  cout << myfile.bad() << endl;
  cout << myfile.eof() << endl;
  cout << buffer << endl;
}
