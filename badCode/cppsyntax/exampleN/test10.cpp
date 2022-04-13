#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

class List {
public:
  int id;
  List *next;

  List() = delete;
  List(int id) {
    this->id = id;
    this-> next = nullptr;
  }
  List(int id, int n) {
    this->id = n;
    this->next = nullptr;
    for (int i = 1; i <= n; i++) {
      this->insert(new List(i));

    }
  }

  void insert(List* node) {
    List* p = this;
    while(p->next) p = p->next;
    p->next = node;
  }

  void remove(int id) {
    List *p = this, *q = nullptr;
    while(p && p->next) {
      if (p->next->id == id) {
        q = p->next;
        p->next = q->next;
        delete q;
        break;
      }
      p = p->next;
    }
  }

  void Print() {
    List* p = this->next;
    while(p) {
      cout << p->id << endl;
      p = p->next;
    }
  }
  void play() {
    int count = 0, third = 2, rid;
    List* p = this->next;
    while(count++ != id - 1) {
      third = 2;
      while(third--) {
        if (p->next != nullptr) p = p->next;
        else p = this->next;
      }
      rid = p->id;
      if (p->next != nullptr) p = p->next;
      else p = this->next;
      remove(rid);
    }
    Print();
  }
};

int main() {
  int n;
  cin >> n;
  List list(0, n);  // head pointer(not use this)
  list.play();

  return 0;
}
