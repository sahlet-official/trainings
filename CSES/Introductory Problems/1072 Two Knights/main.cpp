#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n = 0;
    std::cin >> n;

    vector<long long> first7 = {0, 6, 28, 96, 252, 550, 1056};
    
    for (size_t i = 0; i < min(7, n); i++)
    {
        cout << first7[i] << endl;
    }

    if (n < 8)
    {
        return;
    }

    long long k = 7;
    long long res = first7.back();

    for (; k < n; k++)
    {
        res += 2*k*k*k + 3*k*k - 7*k + 8;
        
        cout << res << endl;
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