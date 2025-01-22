template <int N, typename Flow, typename Cost>
struct Mcmf {
  int n;
  vector<int> adj[N];
  
  struct Edge {
    int to;
    Flow cap;
    Cost cost;
  };

  vector<Edge> es;

  void init(int n_) {
    n = n_;
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
    es.clear();
  }

  int ae(int u, int v, Flow cap, Cost cost) {
    adj[u].push_back(len(es)), es.push_back({v, cap, cost});
    adj[v].push_back(len(es)), es.push_back({u, 0, -cost});
    return len(es) - 2;
  }

  Cost dis[N];
  bool vis[N];

  bool spfa(int s, int t) {
    constexpr Cost inf = numeric_limits<Cost>::max();
    fill_n(dis + 1, n, inf), dis[s] = 0;
    queue<int> q{{s}};
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      vis[u] = false;
      for (int i : adj[u]) {
        Edge e = es[i];
        int v = e.to;
        if (e.cap > 0 && dis[v] > dis[u] + e.cost) {
          dis[v] = dis[u] + e.cost;
          if (!vis[v]) {
            vis[v] = true;
            q.push(v);
          }
        }
      }
    }
    return dis[t] < inf;
  }

  vector<int>::iterator arc[N];

  Flow dfs(int u, int t, Flow f) {
    if (u == t) {
      return f;
    }
    vis[u] = true;
    Flow r = f;
    for (; arc[u] < end(adj[u]); ++arc[u]) {
      Edge &e = es[*arc[u]];
      int v = e.to;
      if (!vis[v] && e.cap > 0 && dis[v] == dis[u] + e.cost) {
        Flow df = dfs(v, t, min(r, e.cap));
        r -= df, e.cap -= df, es[*arc[u] ^ 1].cap += df;
        if (r == 0) {
          break;
        }
      }
    }
    vis[u] = false;
    return f - r;
  }

  pair<Flow, Cost> run(int s, int t) {
    Flow totFlow = 0;
    Cost totCost = 0;
    while (spfa(s, t)) {
      for (int u = 1; u <= n; ++u) {
        arc[u] = begin(adj[u]);
      }
      Flow df = dfs(s, t, numeric_limits<Flow>::max());
      totFlow += df;
      totCost += dis[t] * df;
    }
    return {totFlow, totCost};
  }
};
