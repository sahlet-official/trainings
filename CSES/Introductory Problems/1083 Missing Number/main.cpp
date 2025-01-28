#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n = 0;
    std::cin >> n;
    long long sum = (long long)n * (n + 1) / 2;
    long long missingSum = 0;

    for (size_t i = 0; i < n; i++)
    {
        int number = 0;
        cin >> number;

        missingSum += number;
    }

    cout << (sum - missingSum);
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