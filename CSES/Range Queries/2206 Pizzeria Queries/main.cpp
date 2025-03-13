#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    long long minTreeL[4*maxN], minTreeR[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];

    void pull(int node)
    {
        int l = lowerIndex[node];
        int r = higherIndex[node];
        int m = (l + r) / 2;

        minTreeL[node] = min(minTreeL[2*node] + r - m, minTreeL[2*node + 1]);
        minTreeR[node] = min(minTreeR[2*node], minTreeR[2*node + 1] + m - l + 1);
    }

    void init(int node = 1, int l = 1, int r = N)
    {
        lowerIndex[node] = l;
        higherIndex[node] = r;

        if (l == r)
        {
            indexToNode[l] = node;

            int val = 0;
            scanf("%d", &val);

            minTreeL[node] = val;
            minTreeR[node] = val;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    long long query(int node, int building)
    {
        if (building < lowerIndex[node])
        {
            return minTreeR[node];
        }
        else if (building > higherIndex[node])
        {
            return minTreeL[node];
        }
        else if (building == lowerIndex[node] && building == higherIndex[node])
        {
            return minTreeL[node];
        }

        int m = higherIndex[2*node];

        bool goesToLeft = building <= m;

        long long left = query(2*node, building) + (goesToLeft ? 0 : (building - m));
        long long right = query(2*node + 1, building) + (goesToLeft ? (m + 1 - building) : 0);

        return min(left, right);
    }

    void update(int idx, int val)
    {
        int node = indexToNode[idx];

        minTreeL[node] = val;
        minTreeR[node] = val;

        while(node >= 2)
        {
            node >>= 1;
            pull(node);
        }
    }

    void printTree()
    {
        //return;
        for (int node = 1; node < 2*N; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%lld ", minTreeL[node]);
        }

        for (int node = 1; node < 2*N; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%lld ", minTreeR[node]);
        }
        
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        //printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0;
            scanf("%d", &t);

            if (t == 1)
            {
                int building = 0, price = 0;
                scanf("%d %d", &building, &price);
                update(building, price);
            }
            else if (t == 2)
            {
                int building = 0;
                scanf("%d", &building);
                long long bestPrice = query(1, building);

                printf("%lld\n", bestPrice);
            }
        }
    }
}

namespace solve2
{
    const int maxN = 2e5;
    long long minTree[2][4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];

    void pull(int node)
    {
        minTree[0][node] = min(minTree[0][2*node], minTree[0][2*node + 1]);
        minTree[1][node] = min(minTree[1][2*node], minTree[1][2*node + 1]);
    }

    void init(int node = 1, int l = 1, int r = N)
    {
        lowerIndex[node] = l;
        higherIndex[node] = r;

        if (l == r)
        {
            indexToNode[l] = node;

            int val = 0;
            scanf("%d", &val);

            minTree[0][node] = val - l;
            minTree[1][node] = val + l;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    long long query(int type, int l, int r, int node = 1)
    {
        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            return minTree[type][node];
        }
        else if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return INT_MAX;
        }

        long long left = query(type, l, r, 2*node);
        long long right = query(type, l, r, 2*node + 1);

        return min(left, right);
    }

    void update(int idx, int val)
    {
        int node = indexToNode[idx];

        minTree[0][node] = val - idx;
        minTree[1][node] = val + idx;

        while(node >= 2)
        {
            node >>= 1;
            pull(node);
        }
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0;
            scanf("%d", &t);

            if (t == 1)
            {
                int building = 0, price = 0;
                scanf("%d %d", &building, &price);
                update(building, price);
            }
            else if (t == 2)
            {
                int building = 0;
                scanf("%d", &building);
                long long bestPriceL = query(0, 1, building);
                long long bestPriceR = query(1, building, N);

                printf("%lld\n", min(bestPriceL + building, bestPriceR - building));
            }
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
        //solve1::solve();
        solve2::solve();
    }

    return 0;
}