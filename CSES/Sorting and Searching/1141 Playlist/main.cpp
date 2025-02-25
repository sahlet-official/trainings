#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
unordered_map<int, int> vis(2*maxN);
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    int res = 0;

    int first = 1;
 
    for (int i = 1; i <= n; i++)
    {
        int id = 0;
        scanf("%d", &id);

        if (vis.count(id) == 1)
        {
            int index = vis[id];
            if (index >= first)
            {
                first = index + 1;
            }
        }
        
        vis[id] = i;

        res = max(res, i - first + 1);
    }

    printf("%d", res);
}
 
 
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
 
    long long testsNumber = 1;
 
    //cin >> testsNumber;
 
    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }
 
    return 0;
}