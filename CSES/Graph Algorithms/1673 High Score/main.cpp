#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Bellman–Ford algorithm (SPFA)
{
    const int maxN = 2500;
    const int maxM = 5000;
    const long long bigVal = 1e9 * (long long)(maxN + 1);
    vector<pair<int, int>> neighbors[maxN + 1];
    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long MININF = 0xc0c0c0c0c0c0c0c0;
    long long distance[maxN + 1];

    int N, M;

    queue<int> oneRun(queue<int> q)
    {
        queue<int> res;
        
        while (!q.empty())
        {
            int node = q.front(); q.pop();

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (distance[node] + weight > distance[neighbor])
                {
                    distance[neighbor] = distance[node] + weight;
                    res.push(neighbor);
                }
            }
        }

        return res;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        memset(distance, 0xc0, sizeof(distance));

        queue<int> q;
        q.emplace(1);
        distance[1] = 0;

        for (int i = 1; i < N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }

        long long res = distance[N];

        for (int i = 1; i <= 2*N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }

        for (int i = 1; i <= q.size(); i++)
        {
            distance[q.front()] = bigVal;
            q.push(q.front());
            q.pop();
        }

        for (int i = 1; i <= N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }
        
        printf("%lld", distance[N] == res ? res : -1ll);
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