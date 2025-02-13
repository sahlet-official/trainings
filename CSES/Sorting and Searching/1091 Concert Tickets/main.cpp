#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);

    multiset<int> h;

    for (int i = 0; i < n; i++)
    {
        int val = 0;
        scanf("%d", &val);
        h.insert(-val);
    }

    for (int i = 0; i < m; i++)
    {
        int t = 0;
        scanf("%d", &t);
        auto iter = h.lower_bound(-t);

        if (h.end() == iter)
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", -*iter);
            h.erase(iter);
        }
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