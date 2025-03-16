#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    bool visited[maxN + 1];
    vector<int> neighbors[maxN + 1];
    
    struct NodeInfo
    {
        int from = -1;
        //int length = -1;

        bool visited()
        {
            return from >= 0;
        }
    };

    NodeInfo info[maxN + 1];

    int N, M;

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

        queue<int> q;

        info[1] = {0};
        q.push(1);

        bool found = false;
        
        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            if (node == N)
            {
                found = true;
                break;
            }

            for (int neighbor : neighbors[node])
            {
                if (info[neighbor].visited())
                {
                    continue;
                }

                info[neighbor].from = node;
                q.push(neighbor);
            }
            
        }
        
        if (!found)
        {
            printf("IMPOSSIBLE");
            return;
        }

        deque<int> res;

        for (int i = N; info[i].from > 0; i = info[i].from)
        {
            res.push_front(i);
        }

        res.push_front(1);
        
        printf("%lu\n", res.size());
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
        solve1::solve();
    }

    return 0;
}