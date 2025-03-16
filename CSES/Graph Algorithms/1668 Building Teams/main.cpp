#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    bool visited[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int colors[maxN + 1];
    int N, M;

    bool isVisited(int node)
    {
        return colors[node] != 0;
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

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        stack<int> s;

        bool impossible = false;

        for (int root = getFirstUnvisited(); root <= N && !impossible; root = getFirstUnvisited())
        {
            s.push(root);
            colors[root] = 1;
            
            while (!s.empty() && !impossible)
            {
                int node = s.top();
                s.pop();

                for (int neighbor : neighbors[node])
                {
                    if (isVisited(neighbor))
                    {
                        if (colors[neighbor] == colors[node])
                        {
                            impossible = true;
                            break;
                        }
                        continue;
                    }

                    colors[neighbor] = colors[node] == 1 ? 2 : 1;
                    s.push(neighbor);
                }
                
            }
        }
        
        if (impossible)
        {
            printf("IMPOSSIBLE");
            return;
        }

        deque<int> res;

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", colors[i]);
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
        solve1::solve();
    }

    return 0;
}