#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int arr[maxN];
 
void solve() {
    int n = 0, x = 0;
    scanf("%d%d", &n, &x);

    int res = 0;
 
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    long long sum = 0;

    for (int l = 0, r = 0; l < n;)
    {
        while (sum < x && r <= n)
        {
            sum += arr[r];
            r++;
        }

        if (sum < x)
        {
            break;
        }

        if (sum == x)
        {
            res++;
            sum -= arr[l];
            l++;
        }
        
        while (sum > x && l < r)
        {
            sum -= arr[l];
            l++;
        }
    }

    printf("%d", res);
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