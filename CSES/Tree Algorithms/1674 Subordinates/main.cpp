#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    vector<int> children[maxN + 1];
    int res[maxN + 1];
    int N;

    void dfs(int node)
    {
        res[node] = 1;
        for (int child : children[node])
        {
            dfs(child);
            res[node] += res[child];
        }
    }

    void solve()
    {
        scanf("%d", &N);

        for (int i = 2; i <= N; i++)
        {
            int boss = 0;
            scanf("%d", &boss);

            children[boss].push_back(i);
        }

        dfs(1);

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", res[i] - 1);
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