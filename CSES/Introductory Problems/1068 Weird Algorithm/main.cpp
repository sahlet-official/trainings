#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve(long long n)
{
    while (n != 1)
    {
        cout << n << " ";
        if (n % 2)
        {
            n = 3*n + 1;
        }
        else
        {
            n /= 2;
        }
    }

    cout << n;
}

void solve()
{
    long long n = 0;
    cin >> n;
    solve(n);
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