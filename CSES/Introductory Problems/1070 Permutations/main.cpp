#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n = 0;
    std::cin >> n;

    if (n == 2 || n == 3)
    {
        cout << "NO SOLUTION";
        return;
    }

    for (size_t i = 1; i <= n / 2; i++)
    {
        std::cout << (i + n / 2) << " " << i << " ";
    }

    if (n & 1)
    {
        cout << n;
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