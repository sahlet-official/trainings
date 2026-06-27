#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace Solution1 {
    const int maxN = 3000;
    char res[maxN + maxN - 1];
    char matrix[maxN][maxN + 1];
    bool processed[maxN][maxN];

    void solve() {
        int n = 0;

        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            scanf("%s", matrix[i]);
        }

        for (int i = 0; i < (n + n - 1); i++) {
            res[i] = 'Z';
        }
        

        vector<pair<int, int>> curCellVariants, nextCellVariants;
        curCellVariants.reserve(n + n - 1);
        nextCellVariants.reserve(n + n - 1);

        res[0] = matrix[0][0];

        if (n > 1) {
            curCellVariants.emplace_back(0, 1);
            curCellVariants.emplace_back(1, 0);
        }

        while (!curCellVariants.empty()) {
            for (auto& cell : curCellVariants) {
                if (processed[cell.first][cell.second]) {
                    continue;
                }

                if (matrix[cell.first][cell.second] <= res[cell.first + cell.second]) {
                    if (matrix[cell.first][cell.second] < res[cell.first + cell.second]) {
                        nextCellVariants.clear();
                    }

                    res[cell.first + cell.second] = matrix[cell.first][cell.second];

                    if (cell.first + 1 < n) {
                        nextCellVariants.emplace_back(cell.first + 1, cell.second);
                    }
                    if (cell.second + 1 < n) {
                        nextCellVariants.emplace_back(cell.first, cell.second + 1);
                    }
                }

                processed[cell.first][cell.second] = true;
            }        

            std::swap(curCellVariants, nextCellVariants);
            nextCellVariants.clear();
        }
        
        for (int i = 0; i < (n + n - 1); i++) {
            printf("%c", res[i]);
        }
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
    // scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        Solution1::solve();
    }

    return 0;
}