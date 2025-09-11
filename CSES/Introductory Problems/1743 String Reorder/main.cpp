#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int max_n = 1e6;
    int n;
    char str[max_n + 1];
    char res[max_n + 1];
    int set[26];

    inline char getMin() {
        int order = 0;
        while (order < 26 && !set[order]) {
            order++;
        }

        if (order == 26) {
            return -1;
        }

        return 'A' + order;
    }

    inline char getSecondMin() {
        int order = 0;
        while (order < 26 && !set[order]) {
            order++;
        }

        if (order == 26) {
            return -1;
        }

        order++;

        while (order < 26 && !set[order]) {
            order++;
        }

        if (order == 26) {
            return -1;
        }

        return 'A' + order;
    }

    inline int getMaxCountIndex() {
        int maxIndex = 0;
        int order = 0;
        while (order < 26) {
            maxIndex = set[order] > set[maxIndex] ? order : maxIndex;
            order++;
        }

        return maxIndex;
    }

    void solve()
    {
        scanf("%s", str);

        int strlen = 0;
        {
            int i = 0;
            while (str[i]) {
                set[str[i] - 'A']++;
                strlen++;
                i++;
            }
        }

        int maxCountIndex = getMaxCountIndex();

        if ((2 * set[maxCountIndex] - 1) > strlen) {
            printf("-1");
            return;
        }

        bool min = true;
        for (int i = 0; i < strlen; i++) {
            int maxCountIndex = getMaxCountIndex();
            char ch = min ? getMin() : getSecondMin();

            int rest = strlen - i;
            if ((maxCountIndex + 'A') != ch && (2 * set[maxCountIndex] - 1) == rest) {
                res[i] = maxCountIndex + 'A';
                set[maxCountIndex]--;
                min = true;

                continue;
            }

            // if (ch == -1) {
            //     printf("-1");
            //     return;
            // }

            set[ch - 'A']--;
            res[i] = ch;
            // printf("%s\n", res);

            if (min && set[ch - 'A'] == 0) {
                min = true;
            } else {
                min = !min;
            }
        }

        res[strlen] = '\0';

        printf("%s", res);
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