#include <assert.h>
#include <iostream>
#include <set>
#include <vector>

const size_t NMAX = 205;
const int64_t MAXCOST = 10000000000000;
const int INF = 1000000000;

struct edge {
    size_t from;
    size_t to;
    int cap, flow;
    int64_t cost;
    size_t num;
};


std::vector<int64_t> phi, dist;

size_t n, m;
std::vector<edge> edges;
std::vector<size_t> g[NMAX];
std::vector<int> par;

void add_edge(size_t v, size_t u, int cap, int64_t cost, size_t num) {
    g[v].push_back(edges.size());
    edges.push_back({v, u, cap, 0, cost, num});
    g[u].push_back(edges.size());
    edges.push_back({u, v, 0, 0, -cost, num});
}

void countPhi() {
    size_t start = 1;
    fill(phi.begin(), phi.end(), MAXCOST);
    phi[start] = 0;
    std::set<std::pair<int64_t, int>> S;
    S.insert({phi[start], start});
    while (S.size()) {
        auto v = S.begin()->second;
        S.erase(S.begin());
        for (auto &t : g[v]) {
            if (edges[t].cap == edges[t].flow) {
                continue;
            }
            size_t u = edges[t].to;
            if (phi[v] + edges[t].cost < phi[u]) {
                S.erase({phi[u], u});
                phi[u] = phi[v] + edges[t].cost;
                S.insert({phi[u], u});
            }
        }
    }
}

void dijkstra(size_t start) {
    fill(dist.begin(), dist.end(), MAXCOST);
    fill(par.begin(), par.end(), INF);
    par[start] = -1;
    dist[start] = 0;
    std::set<std::pair<int64_t, int>> S;
    S.insert({dist[start], start});
    while (S.size()) {
        auto v = S.begin()->second;
        S.erase(S.begin());
        for (auto &t : g[v]) {
            size_t u = edges[t].to;
            int64_t w = edges[t].cost + phi[v] - phi[u];
            if (edges[t].flow < edges[t].cap && dist[v] + w < dist[u]) {
                S.erase({dist[u], u});
                par[u] = static_cast<int>(t);
                dist[u] = dist[v] + w;
                S.insert({dist[u], u});
            }
        }
    }
}


int countFlow(size_t sink) {
    int flow = INF;
    size_t cur = sink;

    while (true) {
        int i = par[cur];
        if (i == -1) break;
        size_t from = edges[i].from;
        size_t to = edges[i].to;
        assert(to == cur);
        flow = std::min(flow, edges[i].cap - edges[i].flow);
        cur = from;
    }

    cur = sink;
    while (true) {
        int i = par[cur];
        if (i == -1) break;
        edges[i].flow += flow;
        edges[i ^ 1].flow -= flow;
        size_t from = edges[i].from;
        cur = from;
    }
    return flow;
}

int find_flow(size_t source, size_t sink, int k) {
    int flow = 0;
    dist.resize(NMAX, MAXCOST);
    par.resize(NMAX);
    countPhi();
    while (true) {
        dijkstra(source);
        if (dist[sink] == MAXCOST) {
            break;
        }
        while (int cur_flow = countFlow(n)) {
            flow += cur_flow;
            if (flow == k) {
                break;
            }
        }
        for (size_t i = 1; i <= n; ++i) {
            phi[i] = std::min(MAXCOST, phi[i] + dist[i]);
        }
        if (flow == k) {
            break;
        }
    }
    return flow;
}

std::vector<size_t> Ans;
int64_t sumAns;
std::vector<bool> used;

void dfs_ans(size_t v) {
    used[v] = true;
    if (v == n)
        return;
    for (auto &t : g[v]) {
        size_t u = edges[t].to;
        if (used[u]) continue;
        if (edges[t].flow > 0) {
            Ans.push_back(edges[t].num);
            sumAns += edges[t].cost;
            edges[t].flow = 0;
            edges[t ^ 1].flow = 0;
            return dfs_ans(u);
        }
    }
}

int main() {
#if __APPLE__
    freopen("/Users/macbook/ClionProjects/untitled/input.txt", "r", stdin);
    freopen("/Users/macbook/ClionProjects/untitled/output.txt", "w", stdout);
#else
    //        freopen("lca2.in", "r", stdin);
//    freopen("lca2.out", "w", stdout);
#endif
    int k;
    std::cin >> n >> m >> k;
    phi.resize(NMAX);
    for (size_t i = 0; i < m; ++i) {
        size_t v, u;
        int cap = 1;
        int64_t cost;
        std::cin >> v >> u >> cost;
        add_edge(v, u, cap, cost, i);
        add_edge(u, v, cap, cost, i);
    }
    int64_t all_flow = find_flow(1, n, k);
    if (all_flow < k) {
        std::cout << -1 << std::endl;
        return 0;
    }
    int64_t all_cost = 0;
    std::vector<std::vector<size_t>> out;
    used.resize(NMAX, 0);
    for (size_t i = 0; i < k; ++i) {
        Ans.clear();
        fill(used.begin(), used.end(), 0);
        sumAns = 0;
        dfs_ans(1);
        out.push_back(Ans);
        all_cost += sumAns;
    }
    std::cout.precision(20);
    std::cout << static_cast<double>(all_cost) / k << std::endl;
    for (auto &t : out) {
        std::cout << t.size() << ' ';
        for (auto &q : t) {
            std::cout << q + 1 << ' ';
        }
        std::cout << std::endl;
    }
}
