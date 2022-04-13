#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// https://www.geeksforgeeks.org/csv-file-management-using-c/

class Scores {
public:
  std::string name;
  double chuSc;
  double fuSc;
  double allSc;
  Scores() : name(""), chuSc(0), fuSc(0), allSc(0) {}
  Scores(std::string name, double chuSc, double fuSc) : name(name), chuSc(chuSc), fuSc(fuSc) {
    allSc = (chuSc / 5.0l) * 0.7 + fuSc * 0.3;
  }
  void count() {
    allSc = (chuSc / 5.0l) * 0.7 + fuSc * 0.3;
  }
  void print() {
    std::cout << name << ',' << allSc << std::endl;
  }
};

class cCSVFile {
private:
  std::fstream file;
  std::vector<Scores> scores;
public:
  cCSVFile(std::string fileName) {
    file.open(fileName);
    if (!file.is_open()) {
      std::cout << fileName << " cannot be opened!!!\n";
      exit(EXIT_FAILURE);
    }
  }

  // 输出文件内容到output
  void printFile() {
    std::string line;
    if (file.good()) {
      while (getline(file, line)) {
        std::cout << line << std::endl;
      }
    }
  }

  // reading CSV file
  void readCSV() {
    std::string line, word;
    if (file.good()) {
      // 读取第一行
      getline(file, line);
      while (getline(file, line)) {
        Scores score;
        // used for breaking words
        std::stringstream sbuf(line);
        // while (getline(sbuf, word, ',')) {
        //   std::cout << word << std::endl;
        // }
        getline(sbuf, word, ',');
        score.name = word;
        getline(sbuf, word, ',');
        score.chuSc = stod(word);
        getline(sbuf, word, ',');
        score.fuSc = stod(word);
        score.count();
        scores.push_back(score);
      }
    }
  }

  // print scores
  void printScores() {
    int count = 0;
    for (auto i : scores) {
      std::cout << ++count << ',';
      i.print();
    }
  }

  void sortScores() {
    std::sort(scores.begin(), scores.end(), [](Scores a, Scores b){
          return a.allSc > b.allSc;
        });
  }

  // FIXME: 拉跨
  void writeToCSV() {
    std::ofstream ofile("temp.csv");
    if (!ofile.is_open()) {
      std::cout << "cannot open this file!!!\n";
      return;
    }
    ofile << "排名,姓名,总成绩\n";
    for (int i = 0; i < (int)scores.size(); i++) {
      ofile << i + 1 << ',' << scores[i].name << ',' << scores[i].allSc << '\n';
    }
    ofile.close();
  }

  ~cCSVFile() {
    file.close();
  }
};

int main() {
  cCSVFile csv("./information.csv");
  // csv.printFile();
  csv.readCSV();
  csv.sortScores();
  csv.writeToCSV();
  return 0;
}
