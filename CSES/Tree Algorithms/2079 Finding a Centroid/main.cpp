#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
namespace solve1
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int sizes[maxN + 1];
    int res = 0;
    int N;
 
    void dfs(int node = 1, int parent = 0)
    {
        sizes[node] = 1;
        
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) {
                dfs(neighbor, node);
                sizes[node] += sizes[neighbor];
            }

            if (res)
            {
                return;
            }
        }

        if (res)
        {
            return;
        }

        if (sizes[node] > N / 2)
        {
            res = node;
        }
    }
 
    void solve()
    {
        scanf("%d", &N);
 
        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
 
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
 
        dfs();

        printf("%d ", res);
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