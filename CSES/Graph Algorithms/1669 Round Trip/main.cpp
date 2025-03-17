#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int from[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;

    bool isVisited(int node)
    {
        return from[node] >= 0;
    }

    int unvisited = 1;
    int getFirstUnvisited()
    {
        while (unvisited <= N && isVisited(unvisited))
        {
            unvisited++;
        }
        return unvisited;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        memset(from, -1, sizeof(from));

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        stack<int> s;

        deque<int> res;

        for (int root = getFirstUnvisited(); root <= N && res.empty(); root = getFirstUnvisited())
        {
            s.push(root);
            from[root] = 0;
            
            while (!s.empty() && res.empty())
            {
                int node = s.top();
                s.pop();

                for (int neighbor : neighbors[node])
                {
                    if (isVisited(neighbor))
                    {
                        if (from[node] != neighbor)
                        {
                            int cycleStart = from[neighbor];
                            res.push_back(cycleStart);
                            res.push_back(neighbor);
                            
                            int parent = node;
                            
                            while (parent != cycleStart) {
                                res.push_back(parent);
                                parent = from[parent];
                            }

                            res.push_back(cycleStart);

                            break;
                        }

                        continue;
                    }

                    s.push(neighbor);

                    from[neighbor] = node;
                }
                
            }
        }
        
        if (res.empty())
        {
            printf("IMPOSSIBLE");
            return;
        }

        printf("%d\n", (int)res.size());

        for (int i = 0; i < res.size(); i++)
        {
            printf("%d ", res[i]);
        }
    }
}

namespace solve2
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int from[maxN + 1];
    bool vis[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;

    int unvisited = 1;
    int getFirstUnvisited()
    {
        while (unvisited <= N && vis[unvisited])
        {
            unvisited++;
        }
        return unvisited;
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

        stack<int> s;

        deque<int> res;

        for (int root = getFirstUnvisited(); root <= N && res.empty(); root = getFirstUnvisited())
        {
            s.push(root);
            from[root] = 0;
            
            while (!s.empty() && res.empty())
            {
                int node = s.top();
                s.pop();
                vis[node] = true;

                for (int neighbor : neighbors[node])
                {
                    if (vis[neighbor])
                    {
                        if (from[node] != neighbor)
                        {
                            res.push_back(neighbor);
                            
                            int parent = node;
                            
                            while (parent != neighbor) {
                                res.push_back(parent);
                                parent = from[parent];
                            }

                            res.push_back(neighbor);

                            break;
                        }

                        continue;
                    }

                    s.push(neighbor);
                    from[neighbor] = node;
                }
                
            }
        }
        
        if (res.empty())
        {
            printf("IMPOSSIBLE");
            return;
        }

        printf("%d\n", (int)res.size());

        for (int i = 0; i < res.size(); i++)
        {
            printf("%d ", res[i]);
        }
    }
}

namespace solve3
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int from[maxN + 1];
    bool vis[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;
    deque<int> res;

    int unvisited = 1;
    int getFirstUnvisited()
    {
        while (unvisited <= N && vis[unvisited])
        {
            unvisited++;
        }
        return unvisited;
    }

    bool dfs(int node)
    {
        vis[node] = true;

        for (int neighbor : neighbors[node])
        {
            if (vis[neighbor])
            {
                if (from[node] != neighbor)
                {
                    res.push_back(neighbor);
                    
                    int parent = node;
                    
                    while (parent != neighbor) {
                        res.push_back(parent);
                        parent = from[parent];
                    }

                    res.push_back(neighbor);

                    return true;
                }

                continue;
            }

            from[neighbor] = node;
            if (dfs(neighbor))
            {
                return true;
            }
        }

        return false;
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

        for (int root = getFirstUnvisited(); root <= N && res.empty(); root = getFirstUnvisited())
        {   
            dfs(root);
        }
        
        if (res.empty())
        {
            printf("IMPOSSIBLE");
            return;
        }

        printf("%d\n", (int)res.size());

        for (int i = 0; i < res.size(); i++)
        {
            printf("%d ", res[i]);
        }
    }
}

namespace solve4
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    int from[maxN + 1];
    bool vis[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;
    deque<int> res;

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

    bool dfs(int node)
    {
        vis[node] = true;

        for (int neighbor : neighbors[node])
        {
            if (vis[neighbor])
            {
                if (from[node] != neighbor)
                {
                    res.push_back(neighbor);
                    
                    int parent = node;
                    
                    while (parent != neighbor) {
                        res.push_back(parent);
                        parent = from[parent];
                    }

                    res.push_back(neighbor);

                    return true;
                }

                continue;
            }

            from[neighbor] = node;
            if (dfs(neighbor))
            {
                return true;
            }
        }

        return false;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        UnionFind uf(N + 1);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
            
            if (!uf.connect(a, b))
            {
                dfs(a);
                break;
            }
        }
        
        if (res.empty())
        {
            printf("IMPOSSIBLE");
            return;
        }

        printf("%d\n", (int)res.size());

        for (int i = 0; i < res.size(); i++)
        {
            printf("%d ", res[i]);
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