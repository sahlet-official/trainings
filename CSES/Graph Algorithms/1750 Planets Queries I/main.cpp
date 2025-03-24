#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Successor paths, Sparse table
{
    const int maxN = 2e5;
    const int maxK = 1e9;
    const int maxJump = ceil(log2(maxK)) - 1;
    int successors[maxN + 1][maxJump + 1];

    int N, Q;

    void init()
    {
        for (int jump = 1; jump <= maxJump; jump++)
        {
            for (int node = 1; node <= N; node++)
            {
                successors[node][jump] = successors[successors[node][jump-1]][jump-1];
            }
        }
    }

    int getSuccessor(int node, int jumps)
    {
        for (int jump = maxJump; jump >= 0; jump--)
        {
            if ((1 << jump) <= jumps)
            {
                node = successors[node][jump];
                jumps -= (1 << jump);
            }
        }

        return node;
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        for (int i = 1; i <= N; i++)
        {
            int a = 0;
            scanf("%d", &a);
            successors[i][0] = a;
        }

        init();

        for (int i = 1; i <= Q; i++)
        {
            int node = 0, jumps = 0;
            scanf("%d%d", &node, &jumps);

            int successor = getSuccessor(node, jumps);

            printf("%d\n", successor);
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