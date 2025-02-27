#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
typedef array<int, 3> RangeT;
RangeT rangesArr[maxN];
int res[2][maxN];
 
void solve() {
    int n = 0;
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int x = 0, y = 0;
        scanf("%d%d", &x, &y);

        rangesArr[i] = {x, y, i};
    }

    sort(rangesArr, rangesArr + n, [](const RangeT& l, const RangeT& r)
    {
        return l[0] == r[0] ? l[1] > r[1] : l[0] < r[0];
    });

    int maxY = 0;
    for (int i = 0; i < n; i++)
    {
        int curY = rangesArr[i][1];

        res[1][rangesArr[i][2]] = curY <= maxY;
        maxY = max(maxY, curY);
    }

    int minY = INT_MAX;
    for (int i = n - 1; i >= 0; i--)
    {
        int curY = rangesArr[i][1];

        res[0][rangesArr[i][2]] = curY >= minY;
        minY = min(minY, curY);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", res[0][i]);
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", res[1][i]);
    }
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