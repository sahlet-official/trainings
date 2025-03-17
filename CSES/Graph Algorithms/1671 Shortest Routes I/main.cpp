#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Dijkstra’s algorithm
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    //bool visited[maxN + 1];
    vector<pair<int, int>> neighbors[maxN + 1];

    long long INF = 0x3fffffffffffffff;
    
    struct NodeInfo
    {
        //int from = -1;
        long long distance = INF;
        bool visited = false;
    };

    NodeInfo info[maxN + 1];

    int N, M;

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

        info[1].distance = 0;
        q.push({0, 1});
        
        while (!q.empty())
        {
            int node = q.top().second; q.pop();

            if (info[node].visited)
            {
                continue;
            }

            info[node].visited = true;

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (info[node].distance + weight < info[neighbor].distance)
                {
                    info[neighbor].distance = info[node].distance + weight;
                    q.push({info[neighbor].distance, neighbor});
                }
            }
        }
        
        for (int i = 1; i <= N; i++)
        {
            printf("%lld ", info[i].distance);
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