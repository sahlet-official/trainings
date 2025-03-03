#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
pair<int, int> tasks[maxN];
int n;
 
void solve() {
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int a = 0, b = 0;
        scanf("%d%d", &a, &b);

        tasks[i] = {a, b};
    }

    sort(tasks, tasks + n);

    long long timeMoment = 0;
    long long res = 0;

    for (int i = 0; i < n; i++)
    {
        timeMoment += tasks[i].first;

        res += tasks[i].second - timeMoment;
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