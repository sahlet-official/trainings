#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int arr[maxN];
int N, K;

bool can(long long val)
{
    long long sum = 0;
    int k = 1;
    for (int i = 0; i < N && k <= K; i++)
    {
        sum += arr[i];

        if (sum > val)
        {
            k++;
            sum = arr[i];
        }
    }

    return k <= K;
}
 
void solve() {
    scanf("%d%d", &N, &K);

    long long l = 1, r = 1e18;
 
    for (int i = 0; i < N; i++)
    {
        int val = 0;
        scanf("%d", &val);

        arr[i] = val;

        l = max(l, (long long)val);
    }

    while (l < r)
    {
        long long m = (l + r) / 2;
        if (can(m))
        {
            r = m;
        }
        else
        {
            l = m + 1;
        }
    }

    printf("%lld", l);
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