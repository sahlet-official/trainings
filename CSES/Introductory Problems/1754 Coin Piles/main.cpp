#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int a = 0, b = 0;
    cin >> a >> b;

    int x3 = 2*a - b;

    if (x3 < 0 || x3 % 3)
    {
        cout << "NO" << endl;
        return;
    }

    int y = a - 2*(x3 / 3);

    if (y < 0)
    {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}