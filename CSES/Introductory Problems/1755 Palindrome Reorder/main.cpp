#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int max_n = (int)1e6;
    char str[max_n + 1];
    int counts[26];

    void solve()
    {
        scanf("%s", str);
        
        int i = 0;
        while (str[i])
        {
            char cur = str[i];

            counts[cur - 'A']++;

            i++;
        }

        bool odd = false;
        int oddIndex = 0;

        for (int i = 0; i < 26; i++)
        {
            if (counts[i] % 2) {
                if (odd) {
                    printf("NO SOLUTION");
                    return;
                }
                oddIndex = i;
                odd = true;
            }
        }

        for (int i = 0; i < 26; i++)
        {
            if (odd && oddIndex == i) {
                continue;
            }

            for (int j = 0; j < counts[i] / 2; j++)
            {
                printf("%c", 'A' + i);
            }
        }

        if (odd) {
            for (int j = 0; j < counts[oddIndex]; j++)
            {
                printf("%c", 'A' + oddIndex);
            }
        }
        
        for (int i = 25; i >= 0; i--)
        {
            if (odd && oddIndex == i) {
                continue;
            }

            for (int j = 0; j < counts[i] / 2; j++)
            {
                printf("%c", 'A' + i);
            }
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