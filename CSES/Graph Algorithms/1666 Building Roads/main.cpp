#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    bool visited[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;
    int components = 0;
    int componentRoots[maxN + 1];
    
    int unvisited = 1;
    int findFirstUnvisited()
    {
        while (visited[unvisited] && unvisited <= N)
        {
            unvisited++;
        }
        
        return unvisited;
    }

    void depthFirstSearch(int root)
    {
        visited[root] = true;

        function<void(int)> func = [&](int node)
        {
            for (int neighbor : neighbors[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    func(neighbor);
                }
            }
        };

        func(root);
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        int prevRoot = 0;

        vector<pair<int, int>> res;

        for (int root = findFirstUnvisited(); root <= N; root = findFirstUnvisited())
        {
            depthFirstSearch(root);
            if (prevRoot)
            {
                res.emplace_back(prevRoot, root);
            }
            prevRoot = root;
        }
        
        printf("%d\n", res.size());
        for (int i = 0; i < res.size(); i++)
        {
            printf("%d %d\n", res[i].first, res[i].second);
        }
    }

}

namespace solve2
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int N, M;
    int unions[maxN + 1];

    int find(int v)
    {
        if (unions[v] < 0) return v;
        unions[v] = find(unions[v]);
        return unions[v];
    }

    bool merge(int u, int v)
    {
        u = find(u); v = find(v);
        if (u == v) return false;
        
        if (unions[v] < unions[u]) swap(u, v);

        unions[u] += unions[v];
        unions[v] = u;

        return true;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        memset(unions, -1, sizeof(unions));

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            merge(a, b);
        }

        vector<pair<int, int>> res;

        for (int i = 2; i <= N; i++)
        {
            if (merge(i - 1, i))
            {
                res.emplace_back(i - 1, i);
            }
        }
        
        printf("%d\n", res.size());
        for (int i = 0; i < res.size(); i++)
        {
            printf("%d %d\n", res[i].first, res[i].second);
        }
    }

}

namespace solve3
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int N, M;

    class UnionFind {
        vector<int> rank, parent;
    
    public:
        UnionFind(int n) {
            rank.resize(n, 0);
            parent.resize(n);
    
            iota(parent.begin(), parent.end(), 0);
        }
    
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
    
        bool connect(int x, int y) {
            int xRoot = find(x);
            int yRoot = find(y);
    
            if (xRoot == yRoot) {
                return false;
            }
    
            // Union by rank
            if (rank[xRoot] < rank[yRoot]) {
                parent[xRoot] = yRoot;
            }
            else if (rank[yRoot] < rank[xRoot]) {
                parent[yRoot] = xRoot;
            }
            else {
                parent[yRoot] = xRoot;
                rank[xRoot]++;
            }
    
            return true;
        }
    
        bool connected(int x, int y)
        {
            return find(x) == find(y);
        }
    };

    void solve()
    {
        scanf("%d%d", &N, &M);

        UnionFind unionF(N + 1);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            unionF.connect(a, b);
        }

        vector<pair<int, int>> res;

        for (int i = 2; i <= N; i++)
        {
            if (unionF.connect(i - 1, i))
            {
                res.emplace_back(i - 1, i);
            }
        }
        
        printf("%d\n", res.size());
        for (int i = 0; i < res.size(); i++)
        {
            printf("%d %d\n", res[i].first, res[i].second);
        }
    }

}

namespace solve4
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int N, M;

    class UnionFind {
        vector<int> info;
    
    public:
        UnionFind(int n) {
            info.resize(n, -1);
        }
    
        int find(int x) {
            if (info[x] < 0) return x;
            info[x] = find(info[x]);
            return info[x];
        }
    
        bool connect(int x, int y) {
            x = find(x);
            y = find(y);
    
            if (x == y) {
                return false;
            }
    
            // Union by rank
            if (info[x] < info[y]) {
                swap(x, y);
            }

            info[x] = y;
            info[y]--;
    
            return true;
        }
    
        bool connected(int x, int y)
        {
            return find(x) == find(y);
        }
    };

    void solve()
    {
        scanf("%d%d", &N, &M);

        UnionFind unionF(N + 1);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            unionF.connect(a, b);
        }

        vector<pair<int, int>> res;

        for (int i = 2; i <= N; i++)
        {
            if (unionF.connect(i - 1, i))
            {
                res.emplace_back(i - 1, i);
            }
        }
        
        printf("%d\n", res.size());
        for (int i = 0; i < res.size(); i++)
        {
            printf("%d %d\n", res[i].first, res[i].second);
        }
    }

}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        //solve1::solve();
        //solve2::solve();
        //solve3::solve();
        solve4::solve();
    }

    return 0;
}