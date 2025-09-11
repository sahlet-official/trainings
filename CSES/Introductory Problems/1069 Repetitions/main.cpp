#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    char str[(int)1e6 + 1];

    void solve()
    {
        scanf("%s", str);

        int longestSequence = 0;
        int curSequence = 0;
        char prev = '1';

        int i = 0;
        while (str[i])
        {
            char cur = str[i];

            if (prev == cur) {
                curSequence++;
            } else {
                curSequence = 1;
                prev = cur;
            }

            longestSequence = max(longestSequence, curSequence);

            i++;
        }
        
        printf("%d", longestSequence);
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