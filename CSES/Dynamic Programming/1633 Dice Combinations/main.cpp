#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

int memory[(int)1e6 + 1] = {};

void solve() {
    int n = 0;
    cin >> n;

    memory[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = max(i - 6, 0); j < i; j++)
        {
            memory[i] = modSum(memory[i], memory[j]);
        }
    }
    
    cout << memory[n] << endl;
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