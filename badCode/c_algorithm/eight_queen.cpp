/**
 * 回溯算法
 * */
#include <iostream>
#include <vector>
#include <string>

#define COL 8

using namespace std;

vector<vector<string>> solved_queen(int n);
void trackback(vector<vector<string>> &res, vector<string> &board, int row);
bool isValid(vector<string> board, int row, int col);
int get_min(int a, int b) {
  if (a < b)
    return a;
  return b;
}
void getqueenC(int p, int **pa, int n, int *sum);

int main() {
  // vector<vector<string>> res;
  // res = solved_queen(COL);
  // cout << res.size() << endl;
  // int cla = get_min(4, res.size());
  // for (int i = 0; i < cla; i++) {
  //   for (int j = 0; j < COL; j++)
  //     cout << res[i][j] << endl;
  //   cout << endl;
  // }
  int n = 8, sum = 0;
  int *pa[3];

  for (int i = 0; i < 3; i++) {
    pa[i] = new int[2 * n];
  }
  getqueenC(0, pa, n, &sum);
  cout << sum << endl;
  return 0;
}

vector<vector<string>> solved_queen(int n) {
  vector<vector<string>> res;
  vector<string> board(n, string(n, '.'));
  trackback(res, board, 0);
  return res;
}

void trackback(vector<vector<string>> &res, vector<string> &board, int row) {
  // the end condition
  if ((int)board.size() == row) {  // FIXME
    res.push_back(board);
    return;
  }

  int len = board[row].size();

  for (int col = 0; col < len; col++) {
    if (!isValid(board, row, col)) continue;
    board[row][col] = 'Q';
    trackback(res, board, row + 1);
    board[row][col] = '.';
  }
}

bool isValid(vector<string> board, int row, int col) {
  int len = board[row].size();
  // 判断列
  for (int i = 0; i < row; i++)
    if (board[i][col] == 'Q')
      return false;

  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    if (board[i][j] == 'Q')
      return false;

  for (int i = row - 1, j = col + 1; i >= 0 && j < len; i--, j++)
    if (board[i][j] == 'Q')
      return false;

  return true;
}


void getqueenC(int p, int **pa, int n, int *sum) {
  if (p == n) {
    (*sum)++;
    return;
  }
  for (int i = 0; i < n; i++) {
    if (pa[0][i] == 0 && pa[1][p - i + n] == 0 && pa[2][p + i] == 0) {
      pa[0][i] = pa[1][p - i + n] = pa[2][p + i] = 1;
      getqueenC(p + 1, pa, n, sum);
      pa[0][i] = pa[1][p - i + n] = pa[2][p + i] = 0;
    }
  }
}
