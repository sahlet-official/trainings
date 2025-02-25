#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
multiset<int> towersTops;
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        int cube = 0;
        scanf("%d", &cube);

        auto iter = towersTops.upper_bound(cube);
        if (iter != towersTops.end())
        {
            towersTops.erase(iter);
        }
        towersTops.insert(cube);
    }

    printf("%d", (int)towersTops.size());
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