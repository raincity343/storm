template <int N, typename Flow>
struct Dinic {
  int n;
  vector<int> adj[N];
  
  struct Edge {
    int to;
    Flow cap;
  };

  vector<Edge> es;

  void init(int n_) {
    n = n_;
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
    es.clear();
  }

  int ae(int u, int v, Flow cap, Flow rcap = 0) {
    assert(cap >= 0), assert(rcap >= 0);
    adj[u].push_back(len(es)), es.push_back({v, cap});
    adj[v].push_back(len(es)), es.push_back({u, rcap});
    return len(es) - 2;
  }

  int lev[N];

  bool bfs(int s, int t) {
    memset(lev + 1, 0, n * sizeof lev[0]), lev[s] = 1;
    queue<int> q{{s}};
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (int i : adj[u]) {
        Edge e = es[i];
        int v = e.to;
        if (e.cap > 0 && lev[v] == 0) {
          lev[v] = lev[u] + 1, q.push(v);
          if (v == t) {
            return true;
          }
        }
      }
    }
    return false;
  }

  vector<int>::iterator arc[N];

  Flow dfs(int u, int t, Flow f) {
    if (u == t) {
      return f;
    }
    Flow r = f;
    for (; arc[u] < end(adj[u]); ++arc[u]) {
      Edge &e = es[*arc[u]];
      int v = e.to;
      if (e.cap > 0 && lev[v] == lev[u] + 1) {
        Flow df = dfs(v, t, min(r, e.cap));
        r -= df, e.cap -= df, es[*arc[u] ^ 1].cap += df;
        if (r == 0) {
          break;
        }
      }
    }
    return f - r;
  }

  Flow run(int s, int t) {
    Flow tot = 0;
    while (bfs(s, t)) {
      for (int u = 1; u <= n; ++u) {
        arc[u] = begin(adj[u]);
      }
      tot += dfs(s, t, numeric_limits<Flow>::max());
    }
    return tot;
  }
};
