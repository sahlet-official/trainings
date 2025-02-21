#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
int x[200000];

void solve()
{
int n = 0;
scanf("%d", &n);

for (int i = 0; i < n; i++)
{
scanf("%d", &x[i]);
}

sort(x, x+n);

int median = x[n/2];
long long res = 0;

for (int i = 0; i < n; i++)
{
res += abs(x[i] - median);
}

printf ("%lld", res);
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