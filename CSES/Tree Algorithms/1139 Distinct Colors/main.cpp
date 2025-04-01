#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
namespace solve1
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int colors[maxN + 1];
    set<int> colorsInSubtree[maxN + 1];
    int res[maxN + 1];
    int N;
 
    void dfs(int node = 1, int parent = 0)
    {
        colorsInSubtree[node].insert(colors[node]);
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) {
                dfs(neighbor, node);
                if (colorsInSubtree[node].size() < colorsInSubtree[neighbor].size())
                {
                    swap(colorsInSubtree[node], colorsInSubtree[neighbor]);
                }

                for (int color : colorsInSubtree[neighbor])
                {
                    colorsInSubtree[node].insert(color);
                }
            }
        }

        res[node] = colorsInSubtree[node].size();
    }
 
    void solve()
    {
        scanf("%d", &N);
 
        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);
 
            colors[i] = val;
        }
 
        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
 
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
 
        dfs();

        for (int i = 1; i <= N; i++)
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