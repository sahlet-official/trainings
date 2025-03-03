#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int machines[maxN];
int t, n;

bool fits(long long time)
{
    int rest = t;
    for (int i = 0; i < n && rest > 0; i++)
    {
        int produced = time / machines[i];
        if (produced)
        {
            rest -= produced;
        }
        else
        {
            break;
        }
    }

    return rest <= 0;
}
 
void solve() {
    scanf("%d%d", &n, &t);
 
    for (int i = 0; i < n; i++)
    {
        int m = 0;
        scanf("%d", &m);

        machines[i] = m;
    }

    sort(machines, machines + n);

    long long l = machines[0], r = (long long)t * machines[0];

    while (l != r)
    {
        long long m = (r + l) / 2;
        if (fits(m))
        {
            r = m;
        }
        else
        {
            l = m + 1;
        }
    }

    printf("%lld", l);
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