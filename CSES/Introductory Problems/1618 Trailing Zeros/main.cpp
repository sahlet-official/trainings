#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n = 0;
    cin >> n;

    int res = 0;

    long long i = 5;

    while (n >= i)
    {
        res += n / i;
        i *= 5;
    }

    cout << res;
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