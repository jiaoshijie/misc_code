#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct problem_info {
  std::string name;
  int finish_time;
  int debug_time;
  problem_info(std::string name, int ft, int dt) : name(name), finish_time(ft), debug_time(dt) {}
};

class team {
  int contest_time;
  int pro_num;
  int read_time;
  std::vector<problem_info> pis;
  int total_time;
  std::vector<std::string> order;

  int limit_time;
  std::vector<int> commit_time;
  std::vector<std::string> so;
  int count;
public:
  team() = delete;
  team(int c, int p, int r) : contest_time(c), pro_num(p), read_time(r) {
    total_time = 0;
    limit_time = contest_time * 60;
    count = 0;
  }

  void read_pro() {
    std::string name;
    int ft, dt;
    for (int i = 0; i < this->pro_num; i++) {
      std::cin >> name >> ft >> dt;
      problem_info p(name, ft, dt);
      this->pis.push_back(p);
    }
  }

  void print_ans() {
    std::cout << "Total Time = " << total_time << std::endl;
    for (auto it = order.begin(); it != order.end(); it++) {
      std::cout << *it << std::endl;
    }
  }

  int justify_times(int time) {
    if (time / 60 && time % 60 == 0) return time / 60 - 1;
    else return time / 60;
  }

  bool is_finish_all_pro(const bool *is_a) {
    for (int i = 0; i < pro_num; i++) {
      if (!is_a[i]) return false;
    }
    return true;
  }

  void solve_pro() {
    int time = read_time;
    bool *is_a = new bool[pro_num]{false};
    dfs(time, is_a);
  }

  void dfs(int time, bool *is_a) {

    if (time > limit_time) return;
    count_time();
    if (is_finish_all_pro(is_a)) return;

    for (int i = 0; i < pis.size(); i++) {
      if (!is_a[i]) {
        int t = time + justify_times(time + pis[i].finish_time) * pis[i].debug_time + pis[i].finish_time;
        count += justify_times(time + pis[i].finish_time);
        so.push_back(pis[i].name);
        commit_time.push_back(t);
        is_a[i] = true;
        dfs(t, is_a);  // NOTICE
        is_a[i] = false;
        count -= justify_times(time + pis[i].finish_time);
        so.pop_back();
        commit_time.pop_back();
      }
    }
  }

  void count_time() {
    int all_t = 0;
    for (auto it = commit_time.begin(); it != commit_time.end(); it++) {
      all_t += *it;
    }
    all_t += 20 * count;
    if (so.size() > order.size() || (so.size() == order.size() && total_time > all_t)) {
      total_time = all_t;
      order = so;
    }
  }

};

int main() {
  int c, p, r;
  std::vector<team> teams;
  std::cin >> c;
  while(c > 0) {
    std::cin >> p >> r;
    team t(c, p, r);
    t.read_pro();
    teams.push_back(t);
    std::cin >> c;
  }
  for (auto it = teams.begin(); it != teams.end(); it++) {
    it->solve_pro();
    it->print_ans();
  }
  return 0;
}
