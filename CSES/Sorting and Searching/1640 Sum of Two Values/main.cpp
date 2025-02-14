#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
void solve() {
    int n = 0, x = 0;
    scanf("%d%d", &n, &x);
 
    unordered_map<int, int> values;
    values.reserve(3*n);
 
    int res1 = 0;
    int res2 = 0;
 
    for (int i = 1; i <= n; i++)
    {
        int v = 0;
        scanf("%d", &v);
        
        if (values.count(v))
        {
            if (2*v == x)
            {
                res1 = i;
                res2 = values[v];
                break;
            }
        }
        else
        {
            values[v] = i;
        }
    }
 
    if (!res1)
    for (auto& [v, i] : values)
    {
        if (values.count(x - v) && values[x - v] != i)
        {
            res1 = i;
            res2 = values[x - v];
            break;
        }
    }
 
    if (!res1)
    {
        printf("IMPOSSIBLE");
    }
    else
    {
        printf("%d %d", res1, res2);
    }
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