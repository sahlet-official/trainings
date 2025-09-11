#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int max_n = 500;
    int n, m;
    char grid[max_n + 1][max_n + 1 + 1];

    inline int exclude(char ch, int set) {
        if (ch == 'A') {
            return set & (15 ^ 1);
        }
        if (ch == 'B') {
            return set & (15 ^ 2);
        }
        if (ch == 'C') {
            return set & (15 ^ 4);
        }
        if (ch == 'D') {
            return set & (15 ^ 8);
        }

        return set;
    }

    inline char gatAvailableChar(int set) {
        if (set & 1) {
            return 'A';
        }
        if (set & 2) {
            return 'B';
        }
        if (set & 4) {
            return 'C';
        }
        if (set & 8) {
            return 'D';
        }

        assert(0);
    }

    void solve()
    {
        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++) {
            scanf("%s", grid[i] + 1);
            for (int j = 1; j <= m; j++) {
                int set = 15;
                set = exclude(grid[i][j], set);
                set = exclude(grid[i-1][j], set);
                set = exclude(grid[i][j-1], set);

                grid[i][j] = gatAvailableChar(set);
            }
        }
        

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                printf("%c", grid[i][j]);
            }

            printf("\n");
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve();
    }

    return 0;
}