#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int N, M, L;
int *talk;
int *is_werewolfs;
int *is_moreThenOne;
int *res;
bool *is_liers;
std::vector<int> recover;
bool done = false;

void print_answer() {
  for(int i = 0; i < M; i++) {
    std::cout << res[i];
    if (i != M - 1)
      std::cout << ' ';
    else
      std::cout << std::endl;
  }
}

void count_answer() {
  int *temp = new int[M];
  int index = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (is_werewolfs[i] == 2) {
      temp[index++] = i + 1;
    }
  }
  int flag = false;
  for (int i = 0; i < M; i++) {
    if (temp[i] > res[i]) {
      flag = true;
      break;
    }
  }
  if (flag) {
    for (int i = 0; i < M; i++)
      res[i] = temp[i];
  }
}

void add_mark(int index, int liers, int &w, bool &ok) {
  int temp = talk[index] * liers;
  if (temp < 0) {
    if (is_werewolfs[(temp * -1) - 1] == 1) {
      ok = false;
      return;
    }
    if (is_werewolfs[(temp * -1) - 1] != 2) {
      w++;
      is_werewolfs[(temp * -1) - 1] = 2;
    } else {
      is_moreThenOne[(temp * -1) - 1]++;
    }
  } else {
    if (is_werewolfs[(temp * -1) - 1] == 2) {
      ok = false;
      return;
    }
    if (is_werewolfs[temp - 1] != 1)
      is_werewolfs[temp - 1] = 1;
    else
      is_moreThenOne[temp - 1]++;
  }
}

// 规则
bool justice(int werewolfs, int liers) {
  if (liers != L) return false;
  int is_werewolf_notLier = 0;
  int prev_wn = -1;
  int is_werewolf_lier = 0;
  int prev_wl = -1;
  for (int i = 0; i < N; i++) {
    if (is_werewolfs[i] == 2) {
      if (is_liers[i]) is_werewolf_lier++;
      else is_werewolf_notLier++;
    }
  }
  if (is_werewolf_lier + is_werewolf_notLier == M) {
    if (is_werewolf_lier == 0 || is_werewolf_notLier == 0) return false;
    return true;
  }
  for (int i = N - 1; i >= 0; i--) {
    if (is_werewolfs[i] == 0) {
      if (is_liers[i]) {
        is_werewolf_lier++;
        prev_wl = i;
      }
      else {
        is_werewolf_notLier++;
        prev_wn = i;
      }
      is_werewolfs[i] = 2;
      recover.push_back(i);
    }
    if (is_werewolf_lier + is_werewolf_notLier == M) {
      if (is_werewolf_lier == 0) {
        is_werewolf_notLier--;
        is_werewolfs[prev_wn] = 0;
      }
      else if (is_werewolf_notLier == 0) {
        is_werewolf_lier--;
        is_werewolfs[prev_wl] = 0;
      }
      else return true;
    }
  }
  return false;
}

void dfs(int n, int werewolfs, int liers) {
  if (liers > L) return;
  if (werewolfs > M) return;

  if(n < 0) {
    if (justice(werewolfs, liers)) {
      count_answer();
      done = true;
    }
    for(int i = 0; i < recover.size(); i++) {
      is_werewolfs[recover[i]] = 0;
    }
    recover.clear();
    return;
  }
  int w = 0;
  bool ok = true;

  if (liers + n + 1 >= L) {
    add_mark(n, 1, w, ok);
    if (ok) {
      dfs(n - 1, werewolfs + w, liers);
      if (is_moreThenOne[std::abs(talk[n]) - 1] == 0)
        is_werewolfs[std::abs(talk[n]) - 1] = 0;
      else
        is_moreThenOne[std::abs(talk[n]) - 1]--;
    }
    w = 0;
    ok = true;
    add_mark(n, -1, w, ok);
    if (ok) {
      is_liers[n] = true;
      dfs(n - 1, werewolfs + w, liers + 1);
      if (is_moreThenOne[std::abs(talk[n]) - 1] == 0)
        is_werewolfs[std::abs(talk[n]) - 1] = 0;
      else
        is_moreThenOne[std::abs(talk[n]) - 1]--;
      is_liers[n] = false;
    }
  }
}

int main() {
  std::cin >> N >> M >> L;
  talk = new int[N];
  is_werewolfs = new int[N]{ 0 };
  is_moreThenOne = new int[N]{ 0 };
  is_liers = new bool[N]{ false };
  res = new int[M]{ 0 };
  for (int i = 0; i < N; i++) {
    std::cin >> talk[i];
  }

  dfs(N - 1, 0, 0);

  if (done)
    print_answer();
  else
    std::cout << "No Solution" << std::endl;
  return 0;
}
