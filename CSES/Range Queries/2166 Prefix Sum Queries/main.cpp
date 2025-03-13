#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    //const int maxN = 2e5;
    const int maxN = 2e2;
    long long prefSumTree[4*maxN], sumTree[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];

    void pull(int node)
    {
        prefSumTree[node] = max(prefSumTree[2*node], sumTree[2*node] + prefSumTree[2*node + 1]);
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
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

            prefSumTree[node] = max(0, val);
            sumTree[node] = val;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    pair<long long, long long> query(int node, int l, int r)
    {
        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            return {prefSumTree[node], sumTree[node]};
        }
        else if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return {0, 0};
        }

        pair<long long, long long> left = query(2*node, l, r);
        pair<long long, long long> right = query(2*node + 1, l, r);

        return { max(left.first, left.second + right.first), left.second + right.second };
    }

    void update(int idx, int val)
    {
        int node = indexToNode[idx];

        sumTree[node] = val;
        prefSumTree[node] = max(0, val);

        while(node >= 2)
        {
            node >>= 1;
            pull(node);
        }
    }

    void printTree()
    {
        return;
        for (int node = 1; node < 2*N; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%lld ", prefSumTree[node]);
        }

        for (int node = 1; node < 2*N; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%lld ", sumTree[node]);
        }
        
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int t = 0;
            int a = 0, b = 0;
            scanf("%d %d %d", &t, &a, &b);

            if (t == 1)
            {
                update(a, b);
                printTree();
            }
            else if (t == 2)
            {
                long long pref = query(1, a, b).first;

                printf("%lld\n", pref);
            }
        }
    }
}

namespace solve2
{
    const int maxN = 2e5;
    long long prefSumTree[4*maxN], sumTree[4*maxN];
    int N, Q, treeWidth;

    void pull(int node)
    {
        prefSumTree[node] = max(prefSumTree[2*node], sumTree[2*node] + prefSumTree[2*node + 1]);
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
    }

    void init()
    {
        treeWidth = 1;
        while (treeWidth < N) treeWidth <<= 1;
        
        for (int node = treeWidth; node < treeWidth + N; node++)
        {
            int val = 0;
            scanf("%d", &val);

            prefSumTree[node] = max(0, val);
            sumTree[node] = val;
        }

        for (int node = treeWidth - 1; node >= 1; node--)
        {
            pull(node);
        }
    }

    long long query(int l, int r)
    {
        l += treeWidth;
        r += treeWidth;

        long long prefL = 0;
        long long sumL = 0;
        
        long long prefR = 0;

        while(l <= r)
        {
            if (l % 2 == 1)
            {
                prefL = max(prefL, sumL + prefSumTree[l]);
                sumL += sumTree[l];
                l++;
            }

            if (r % 2 == 0)
            {
                prefR = max(prefSumTree[r], prefR + sumTree[r]);
                r--;
            }

            l /= 2;
            r /= 2;
        }

        return max(prefL, sumL + prefR);
    }

    void update(int idx, int val)
    {
        int node = idx + treeWidth;

        sumTree[node] = val;
        prefSumTree[node] = max(0, val);

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
            int a = 0, b = 0;
            scanf("%d %d %d", &t, &a, &b);

            if (t == 1)
            {
                update(a-1, b);
            }
            else if (t == 2)
            {
                long long pref = query(a-1, b-1);

                printf("%lld\n", pref);
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