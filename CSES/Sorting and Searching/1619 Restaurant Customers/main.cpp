#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    vector<int> start(n), end(n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &start[i], &end[i]);
    }

    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    int res = 0;
    int cur = 0;
    int iter1 = 0, iter2 = 0;

    while (iter1 < n)
    {
        while (start[iter1] < end[iter2] && iter1 < n)
        {
            cur++;
            iter1++;
        }

        res = max(res, cur);

        while (start[iter1] == end[iter2] && iter1 < n)
        {
            cur++;
            iter1++;
        }

        while (end[iter2] < start[iter1] && iter2 < n)
        {
            cur--;
            iter2++;
        }

        res = max(res, cur);
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