#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    int N;

    void solve()
    {
        scanf("%d", &N);

        int max = 0;
        long long moves = 0;

        scanf("%d", &max);

        for (int i = 2; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            max = std::max(max, val);

            moves += max - val;
        }
        
        printf("%lld", moves);
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