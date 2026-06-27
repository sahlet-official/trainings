#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace Solution1
{
    const int maxN = 1e5;
    const int log2MaxN = ceil(log2(maxN));
    int nextTable[maxN + 2][log2MaxN];
    int resTable[maxN + 2][log2MaxN];
    int buildings[maxN + 1];
    int N, Q, log2N;

    long long query(int l, int r)
    {
        int res = 0;
        res += 1; // it is needed because 'r' building is always out of range [...) - open range on the right
        for (int pow = log2N - 1; pow >= 0; pow--)
        {
            if (nextTable[l][pow] != -1 && nextTable[l][pow] <= r)
            {
                res += resTable[l][pow];
                l = nextTable[l][pow];
            }
        }

        return res;
    }

    void initTable()
    {
        stack<int> s;

        memset(nextTable, -1, sizeof(nextTable));

        for (int idx = N; idx > 0; idx--)
        {
            while (!s.empty() && buildings[idx] >= buildings[s.top()])
            {
                s.pop();
            }

            nextTable[idx][0] = s.empty() ? N + 1 : s.top();
            resTable[idx][0] = 1;

            s.push(idx);
        }

        for (int pow = 1; pow < log2N; pow++)
        {
            for (int idx = 1; idx <= N; idx++)
            {
                if (nextTable[idx][pow - 1] == -1)
                {
                    continue;
                }

                nextTable[idx][pow] = nextTable[nextTable[idx][pow - 1]][pow - 1];
                if (nextTable[idx][pow] != -1)
                {
                    resTable[idx][pow] = resTable[idx][pow - 1] + resTable[nextTable[idx][pow - 1]][pow - 1];
                }
            }
        }
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        log2N = ceil(log2(N));

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            buildings[i] = val;
        }

        initTable();
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            int count = query(a, b);

            printf("%d\n", count);
        }
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
        Solution1::solve();
    }

    return 0;
}