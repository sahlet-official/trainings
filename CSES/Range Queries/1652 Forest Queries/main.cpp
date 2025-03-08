#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e3;

int prefSum[maxN + 1][maxN + 1];

void solve() {
    int n = 0, q = 0;
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++)
    {
        char str[n + 2];
        scanf("%s", str + 1);
        for (int j = 1; j <= n; j++)
        {
            prefSum[i][j] = prefSum[i - 1][j] + prefSum[i][j - 1] - prefSum[i - 1][j - 1] + (str[j] == '*' ? 1 : 0);
        }
    }
    
    for (int i = 0; i < q; i++)
    {
        int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
        scanf("%d%d%d%d", &y1, &x1, &y2, &x2);

        x1--;y1--;

        int res = prefSum[y2][x2] - prefSum[y2][x1] - prefSum[y1][x2] + prefSum[y1][x1];
        
        printf("%d\n", res);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // std::ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}