#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int x = 0, y = 0;
    std::cin >> y >> x;

    int l = max(x, y);

    long long minVal = (long long)(l - 1) * (l - 1) + 1;
    long long maxVal = (long long)l * l;

    if (x == y)
    {
        std::cout << (minVal + maxVal) / 2 << "\n";
        return;
    }

    bool startsFromTop = !(l & 1);

    long long val = 0;

    if (x > y)
    {
        val = startsFromTop ? minVal : maxVal;
        val += (startsFromTop ? 1 : -1) * (y - 1);
    }
    else
    {
        val = startsFromTop ? maxVal : minVal;
        val += (startsFromTop ? -1 : 1) * (x - 1);
    }

    cout << val << "\n";
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    cin >> testsNumber;

    for (size_t i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}