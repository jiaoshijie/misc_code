#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int N, M, L;
int *talk;
int *is_werewolfs;

void print() {
  int count = 0;
  for (int i = N - 1; i >= 0; i--) {
    if(is_werewolfs[i]) {
      std::cout << i + 1;
      count++;
      if (count != M) {
        std::cout << ' ';
      } else {
        std::cout << std::endl;
        return;
      }
    }
  }
}

void dfs(int index, int ws) {
  if (ws == M) {
    int is_werewolf_lier = 0;
    int liers = 0;
    for (int i = 0; i < N; i++) {
      if ((talk[i] > 0 && is_werewolfs[std::abs(talk[i]) - 1]) || (talk[i] < 0 && !is_werewolfs[std::abs(talk[i]) - 1])) {
        liers++;
        if (is_werewolfs[i] == true) is_werewolf_lier++;
      }
    }
    if (liers == L && is_werewolf_lier < M && is_werewolf_lier > 0) {
      print();
      exit(0);
    }
    return;
  }
  if (index < 0) return;
  is_werewolfs[index] = true;
  dfs(index - 1, ws + 1);
  is_werewolfs[index] = false;
  if (index + ws >= M)
    dfs(index - 1, ws);
}

int main() {
  std::cin >> N >> M >> L;
  talk = new int[N];
  is_werewolfs = new int[N]{ false };
  for (int i = 0; i < N; i++) {
    std::cin >> talk[i];
  }
  dfs(N - 1, 0);
  std::cout << "No Solution" << std::endl;
  return 0;
}
