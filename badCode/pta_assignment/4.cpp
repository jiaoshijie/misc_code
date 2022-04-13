#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int N, Q;
long long *C;
struct _order {
  int start, end;
  _order(int i, int j) {
    if (i > j) {
      start = j;
      end = i;
    } else {
      start = i;
      end = j;
    }
  }
};

std::vector<_order> order;

struct Node {
  int left, right;  // 区间的左端点和右端点
  long long value;  // 节点的值
  long long mark;
  Node() : left(0), right(0), value(0), mark(0) {}
  Node(int l, int r, int v = 0) : left(l), right(r), value(v), mark(0) {}
};

class SegmentTree{
  Node *node;
  unsigned int size;
public:
  SegmentTree(int n) {
    size = 4 * n - 1;  // TODO: why;
    node = new Node[size];
  }

  // l: 2n+1, r: 2n+2
  void setup_dfs(int index, int s, int e) {
    node[index].left = s;
    node[index].right = e;
    if (s == e) {
      node[index].value = C[s];
      return;
    }
    setup_dfs(index * 2 + 1, s, (s + e) / 2);
    setup_dfs(index * 2 + 2, (s + e) / 2 + 1, e);
    node[index].value = std::min(node[index * 2 + 1].value, node[index * 2 + 2].value);
  }

  // BUG: segment fault
  long long search_dfs(int index, int s, int e) {
    if (s > node[index].right || e < node[index].left) return INT32_MAX;
    if (s <= node[index].left && e >= node[index].right) return node[index].value;

    push_back(index);

    return std::min(search_dfs(index * 2 + 1, s, e), search_dfs(index * 2 + 2, s, e));
  }

  void update_dfs(long long m_data, int index, int s, int e) {
    if (s > node[index].right || e < node[index].left) return;
    if (s <= node[index].left && e >= node[index].right) {
      node[index].value -= m_data;
      node[index].mark += m_data;
      return;
    }

    push_back(index);
    update_dfs(m_data, index * 2 + 1, s, e);
    update_dfs(m_data, index * 2 + 2, s, e);
    node[index].value = std::min(node[index * 2 + 1].value, node[index * 2 + 2].value);
  }

  void push_back(int index) {
    if(node[index].mark != 0) {
      node[index * 2 + 1].mark += node[index].mark;
      node[index * 2 + 2].mark += node[index].mark;
      node[index * 2 + 1].value -= node[index].mark;
      node[index * 2 + 2].value -= node[index].mark;
      node[index].mark = 0;
    }
  }
};

int main() {
  int start, end;
  std::cin >> N >> Q;
  C = new long long[N - 1];
  SegmentTree st(N);
  for (int i = 0; i < N - 1; i++) {
    std::cin >> C[i];
  }

  // NOTICE: 1-3 => 1-2
  st.setup_dfs(0, 0, N - 2);

  for (int i = 0; i < Q; i++) {
    std::cin >> start >> end;
    _order o(start, end);
    order.push_back(o);
  }

  std::sort(order.begin(), order.end(), [](_order a, _order b) {
      if (a.end == b.end) return a.start < b.start;
      return a.end < b.end;
      });
  long long res = 0;
  for (int i = 0; i < order.size(); i++) {
    long long temp = st.search_dfs(0, order[i].start, order[i].end - 1);
    res += temp;
    st.update_dfs(temp, 0, order[i].start, order[i].end - 1);
  }
  std::cout << res << std::endl;
  return 0;
}
