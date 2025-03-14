#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    long long sumTree[4*maxN];
    struct LazyData {
        long long assign = 0;
        long long increase = 0;
    } lazyPropagation[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];

    void pull(int node)
    {
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
    }

    void assign(int node, long long val)
    {
        lazyPropagation[node].assign = val;
        lazyPropagation[node].increase = 0;
        sumTree[node] = (higherIndex[node] - lowerIndex[node] + 1) * val;
    }

    void increase(int node, long long val)
    {
        if (lazyPropagation[node].assign)
        {
            lazyPropagation[node].assign += val;
            sumTree[node] = (higherIndex[node] - lowerIndex[node] + 1) * lazyPropagation[node].assign;
        }
        else
        {
            lazyPropagation[node].increase += val;
            sumTree[node] += (higherIndex[node] - lowerIndex[node] + 1) * val;
        }
    }

    void push(int node)
    {
        if (lazyPropagation[node].assign)
        {
            assign(2*node, lazyPropagation[node].assign);
            assign(2*node + 1, lazyPropagation[node].assign);
            lazyPropagation[node].assign = 0;
        }
        else if (lazyPropagation[node].increase)
        {
            increase(2*node, lazyPropagation[node].increase);
            increase(2*node + 1, lazyPropagation[node].increase);
            lazyPropagation[node].increase = 0;
        }
    }

    long long querySum(int l, int r, int node = 1)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return 0;
        }

        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            return sumTree[node];
        }

        push(node);
        return querySum(l, r, 2*node) + querySum(l, r, 2*node + 1);
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

            sumTree[node] = val;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    enum class Operation : int
    {
        Assign,
        Increase,
    };

    void update(Operation operation, int l, int r, int val, int node = 1)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return;
        }

        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            if (operation == Operation::Assign)
            {
                assign(node, val);
            }
            else if (operation == Operation::Increase)
            {
                increase(node, val);
            }
            return;
        }

        push(node);
        update(operation, l, r, val, 2*node);
        update(operation, l, r, val, 2*node + 1);
        pull(node);
    }

    // void printTree()
    // {
    //     //return;

    //     int treeWidth = 1;
    //     while (treeWidth < N) treeWidth <<= 1;

    //     for (int node = 1; node < 2*treeWidth; node++)
    //     {
    //         if ((node&(node-1)) == 0)
    //         {
    //             printf("\n");
    //         }
    //         printf("%lld ", sumTree[node]);
    //     }
    //     printf("\n");
    // }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        //printTree();

        for (int i = 1; i <= Q; i++)
        {
            int t = 0, a = 0, b = 0;
            scanf("%d%d%d", &t, &a, &b);

            if (t == 1)
            {
                int x = 0;
                scanf("%d", &x);
                update(Operation::Increase, a, b, x);
            }
            else if (t == 2)
            {
                int x = 0;
                scanf("%d", &x);
                update(Operation::Assign, a, b, x);
            }
            else if (t == 3)
            {
                long long res = querySum(a, b);
                printf("%lld\n", res);
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

    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve();
    }

    return 0;
}