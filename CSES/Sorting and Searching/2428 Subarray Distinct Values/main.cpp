#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int arr[maxN];
unordered_map<int, int> distinct;
 
void solve() {
    int n = 0, k = 0;
    scanf("%d%d", &n, &k);

    distinct.reserve(4 * maxN);
 
    for (int i = 0; i < n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        arr[i] = val;
    }

    long long res = 0;
    int l = 0, r = 0;

    while (l < n)
    {
        while (r < n)
        {
            if (distinct.size() == k && distinct.find(arr[r]) == distinct.end())
            {
                break;
            }

            distinct[arr[r]]++;
            r++;
        }
        
        res += r - l;

        if (--distinct[arr[l]] == 0)
        {
            distinct.erase(arr[l]);
        }

        l++;
    }

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