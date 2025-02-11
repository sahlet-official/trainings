#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

int n = 0, x = 0;
int c[100];

int memory[(int)1e6 + 1] = {};

void solve() {
    cin >> n >> x;

    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }

    memset(memory, 0, sizeof(memory));

    memory[0] = 1;

    for (size_t i = 0; i < x; i++)
    {
        if (memory[i] == 0)
        {
            continue;
        }

        for (int j = 0; j < n; j++)
        {
            if (i + c[j] <= x)
            {
                memory[i + c[j]] = modSum(memory[i + c[j]], memory[i]);
            }
        }
    }

    cout << memory[x] << endl;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}