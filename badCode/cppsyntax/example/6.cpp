#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Leek {
  int x, y; // position
  int d;    // direction
  int f;    // fighting capacity
};

void printA(int **array, const int row, const int col);
void game();
void moveLeeks(int **chessboard, int n, int m, int k, Leek *leek);
void isMove(int **chessboard, Leek *leek, int i, int x, int y);

int main() {
  game();
  return 0;
}

void printA(int **array, const int row, const int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      cout << array[i][j] << "\t";
    }
    cout << endl;
  }
}

void game() {
  // init
  int n, m, k, t;
  cin >> n >> m >> k;
  int **chessboard = new int*[n];
  for (int i = 0; i < m; i++) {
    chessboard[i] = new int[m];
    for (int j = 0; j < m; j++) {
      chessboard[i][j] = -1;
    }
  }
  Leek *leek = new Leek[k];
  for (int i = 0; i < k; i++) {
    cin >> leek[i].x >> leek[i].y >> leek[i].d >> leek[i].f;
    chessboard[leek[i].x][leek[i].y] = i;
  }
  cin >> t;

  // print init chessboard
  printA(chessboard, n, m);

  // start
  while (t--) {
    moveLeeks(chessboard, n, m, k, leek);
  }
  cout << "\n\n";
  // print ended chessboard
  printA(chessboard, n, m);

  // free mem
  delete []chessboard;
  delete []leek;
}

void moveLeeks(int **chessboard, int n, int m, int k, Leek *leek) {
  for (int i = 0; i < k; i++) {
    if (leek[i].d == -1) continue;  // this leek has already died.
    switch (leek[i].d) {
      case 0:
        if (leek[i].y == 0) {
          leek[i].d = 1;
        } else {
          isMove(chessboard, leek, i, -1, 0);
        }
        break;
      case 1:
        if (leek[i].y == n - 1) {
          leek[i].d = 0;
        } else {
          isMove(chessboard, leek, i, +1, 0);
        }
        break;
      case 2:
        if (leek[i].y == 0) {
          leek[i].d = 3;
        } else {
          isMove(chessboard, leek, i, 0, -1);
        }
        break;
      case 3:
        if (leek[i].y == m - 1) {
          leek[i].d = 2;
        } else {
          isMove(chessboard, leek, i, 0, +1);
        }
        break;
    }
  }
}

void isMove(int **chessboard, Leek *leek, int i, int x, int y) {
  int nextp = chessboard[leek[i].x + x][leek[i].y + y];
  if (nextp != -1) {
    if (leek[nextp].f > leek[i].f) {  // next step have a leek and this leek is more strong than i
      chessboard[leek[i].x][leek[i].y] = -1;
      leek[i].d = -1;
      return;
    } else {  // next step have a leek and this leek is less strong than i
      leek[nextp].d = -1;
    }
  }
  chessboard[leek[i].x][leek[i].y] = -1;
  leek[i].x = leek[i].x + x;
  leek[i].y = leek[i].y + y;
  chessboard[leek[i].x][leek[i].y] = i;
}
