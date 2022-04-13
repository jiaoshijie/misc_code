#include <iostream>
#include <vector>

using namespace std;

struct Task {
  vector<int> Hou;
};

int n;
Task *t = nullptr;
int *flag = nullptr;
int *use = nullptr;


void TaskM();
void print(const vector<int>& array);

int main() {
  TaskM();
  return 0;
}

void TaskM() {
  cin >> n;
  t = new Task[n];
  flag = new int[n];
  use = new int[n];
  getchar();
  string temp;
  // 读取数据
  for (int i = 0; i < n; i++) {
    int j = 0;
    getline(cin, temp);
    while(temp[j++] != '(');
    while(temp[j] != ')') {
      if (temp[j] == ',') j++;
      if (temp[j] == 'N') break;
      if (temp[j] == 'T') t[i].Hou.push_back(temp[j + 4] - '0');
      use[temp[j + 4] - '0']++;
      j = j + 5;
    }
  }
  vector<int> array;
  // 判断
  while((int)array.size() != n) {
    for(int i = 0; i < n; i++) {
      if (flag[i] == 0 && use[i] == 0) {
        array.push_back(i);
        int len = t[i].Hou.size();
        while(len--) {
          use[t[i].Hou[len]]--;
        }
        flag[i] = 1;
        break;
      }
    }
  }
  print(array);
}

void print(const vector<int>& array) {
  for (auto it = array.begin(); it != array.end(); it++) {
    cout << "Task" << *it << ' ';
  }
  cout << endl;
}
