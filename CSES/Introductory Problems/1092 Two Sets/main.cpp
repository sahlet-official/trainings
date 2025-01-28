#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n = 0;
    std::cin >> n;
    long long sum = (long long)n * (n + 1) / 2;

    if (sum & 1)
    {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    sum /= 2;

    int l = 1;
    int r = n;
    int maxInFirstSet = -1;
    int extra = -1;

    while(true)
    {
        int m = (l + r) / 2;
        long long sum1 = (long long)m * (m + 1) / 2;

        if (sum1 - sum < 0)
        {
            l = m + 1;
            continue;
        }

        if (sum1 - sum > m)
        {
            r = m - 1;
            continue;
        }

        maxInFirstSet = m;
        extra = sum1 - sum;
        break;
    }

    int countFirst = extra ? maxInFirstSet - 1 : maxInFirstSet;
    
    cout << countFirst << endl;

    for (int i = 1; i < extra; i++)
    {
        cout << i << " ";
    }

    for (int i = extra + 1; i <= maxInFirstSet; i++)
    {
        cout << i << " ";
    }

    cout << endl;
    cout << (n - countFirst) << endl;

    if (extra)
    {
        cout << extra << " ";
    }

    for (int i = maxInFirstSet + 1; i <= n; i++)
    {
        cout << i << " ";
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    solve();

    return 0;
}