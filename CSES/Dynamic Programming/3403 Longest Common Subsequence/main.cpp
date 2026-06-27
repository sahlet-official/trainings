#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace Solution1 {
    enum class RowColumnState : int {
        FreeFree = 0,
        FreeBusy = 1,
        BusyFree = 2,
        BusyBusy = 3,
        FreeBusyOrBusyFree = 4,
    };

    enum class CameFrom : int {
        Left = 0,
        Up = 1,
        Both = 2,
    };

    const int maxNM = 1000;
    int arr1[maxNM + 1], arr2[maxNM + 1];
    int maxSubsequenceLength[maxNM + 1][maxNM + 1];
    RowColumnState rowColumnStates[maxNM + 1][maxNM + 1];
    CameFrom prevs[maxNM + 1][maxNM + 1];
    bool busyRowsForBackPath[maxNM + 1];
    // bool busyColumnsForBackPath[maxNM + 1];

    void solve() {
        int n = 0, m = 0;

        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &arr1[i]);
        }

        for (int i = 1; i <= m; i++)
        {
            scanf("%d", &arr2[i]);
        }

        RowColumnState nextStateFromUp;
        RowColumnState nextStateFromLeft;

        auto moveFromUp = [&](int i, int j) {
            maxSubsequenceLength[i][j] = maxSubsequenceLength[i][j - 1];
            rowColumnStates[i][j] = nextStateFromUp;
            prevs[i][j] = CameFrom::Up;
        };

        auto moveFromLeft = [&](int i, int j) {
            maxSubsequenceLength[i][j] = maxSubsequenceLength[i - 1][j];
            rowColumnStates[i][j] = nextStateFromLeft;
            prevs[i][j] = CameFrom::Left;
        };

        auto moveFromBoth = [&](int i, int j) {
            maxSubsequenceLength[i][j] = maxSubsequenceLength[i - 1][j];
            rowColumnStates[i][j] = RowColumnState::FreeBusyOrBusyFree;
            prevs[i][j] = CameFrom::Both;
        };
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                nextStateFromUp = ((int)rowColumnStates[i][j - 1] & 1) ? RowColumnState::FreeBusy : RowColumnState::FreeFree;
                nextStateFromLeft = ((int)rowColumnStates[i - 1][j] & 2) ? RowColumnState::BusyFree : RowColumnState::FreeFree;
                if (maxSubsequenceLength[i][j - 1] > maxSubsequenceLength[i - 1][j]) {
                    moveFromUp(i, j);
                } else if (maxSubsequenceLength[i][j - 1] < maxSubsequenceLength[i - 1][j]) {
                    moveFromLeft(i, j);
                } else {
                    if (nextStateFromUp == RowColumnState::FreeFree) {
                        moveFromUp(i, j);
                    } else if (nextStateFromLeft == RowColumnState::FreeFree) {
                        moveFromLeft(i, j);
                    } else {
                        moveFromBoth(i, j);
                    }
                }

                if (arr1[i] == arr2[j]) {
                    if (rowColumnStates[i][j] == RowColumnState::FreeFree) {
                        rowColumnStates[i][j] = RowColumnState::BusyBusy;
                        maxSubsequenceLength[i][j]++;
                    }
                }
            }
        }

        int resLength = maxSubsequenceLength[n][m];
        int resSequence[resLength + 1];

        {
            int lastUndefinedValue = resLength;
            int i = n, j = m;

            while (lastUndefinedValue > 0) {
                if ((int)rowColumnStates[i][j] & (int)RowColumnState::BusyFree) {
                    busyRowsForBackPath[j] = true;
                }

                if (rowColumnStates[i][j] == RowColumnState::BusyBusy) {
                    resSequence[lastUndefinedValue] = arr1[i];
                    lastUndefinedValue--;
                }

                if (prevs[i][j] == CameFrom::Up) {
                    j--;
                } else if (prevs[i][j] == CameFrom::Left) {
                    i--;
                } else {
                    if (busyRowsForBackPath[j]) {
                        j--;
                    } else {
                        i--;
                    }
                }
            }
        }

        printf("%d\n", resLength);
        for (int i = 1; i <= resLength; i++) {
            printf("%d ", resSequence[i]);
        }
    }
}

namespace Solution2 {
    enum class CameFrom : int {
        Left = 0,
        Up = 1,
        Diagonal = 2,
    };

    const int maxNM = 1000;
    int arr1[maxNM + 1], arr2[maxNM + 1];
    int maxSubsequenceLength[maxNM + 1][maxNM + 1];
    CameFrom prevs[maxNM + 1][maxNM + 1];

    void solve() {
        int n = 0, m = 0;

        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &arr1[i]);
        }

        for (int i = 1; i <= m; i++)
        {
            scanf("%d", &arr2[i]);
        }

        auto moveFromUp = [&](int i, int j) {
            maxSubsequenceLength[i][j] = maxSubsequenceLength[i][j - 1];
            prevs[i][j] = CameFrom::Up;
        };

        auto moveFromLeft = [&](int i, int j) {
            maxSubsequenceLength[i][j] = maxSubsequenceLength[i - 1][j];
            prevs[i][j] = CameFrom::Left;
        };

        auto moveFromDiagonal = [&](int i, int j) {
            maxSubsequenceLength[i][j] = maxSubsequenceLength[i - 1][j - 1] + 1;
            prevs[i][j] = CameFrom::Diagonal;
        };
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                moveFromUp(i, j);

                if (maxSubsequenceLength[i][j] < maxSubsequenceLength[i - 1][j]) {
                    moveFromLeft(i, j);
                }

                if (arr1[i] == arr2[j] && maxSubsequenceLength[i][j] < (maxSubsequenceLength[i - 1][j - 1] + 1)) {
                    moveFromDiagonal(i, j);
                }
            }
        }

        int resLength = maxSubsequenceLength[n][m];
        int resSequence[resLength + 1];

        {
            int lastUndefinedValue = resLength;
            int i = n, j = m;

            while (lastUndefinedValue > 0) {
                if (prevs[i][j] == CameFrom::Up) {
                    j--;
                } else if (prevs[i][j] == CameFrom::Left) {
                    i--;
                } else if (prevs[i][j] == CameFrom::Diagonal) {
                    resSequence[lastUndefinedValue] = arr1[i];
                    lastUndefinedValue--;
                    i--;
                    j--;
                }
            }
        }

        printf("%d\n", resLength);
        for (int i = 1; i <= resLength; i++) {
            printf("%d ", resSequence[i]);
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
        // Solution1::solve();
        Solution2::solve();
    }

    return 0;
}