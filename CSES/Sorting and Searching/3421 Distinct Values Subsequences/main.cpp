#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const long long MOD = 1e9 + 7;

inline long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

const int maxN = 2 * 1e5;
int N;
unordered_map<int /*val*/ , int /*count*/> counts;
 
void solve() {
    scanf("%d", &N);

    counts.reserve(3*N);
 
    for (int i = 0; i < N; i++) {
        int val = 0;
        scanf("%d", &val);

        counts[val]++;
    }

    long long res = 1;

    for (auto& pair : counts)
    {
        res = modMult(res, pair.second + 1);
    }

    res = modSum(res, -1);

    printf("%lld", res);
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