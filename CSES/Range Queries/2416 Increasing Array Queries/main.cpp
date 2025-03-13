#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    long long sumTree[maxN + 1], countTree[4*maxN];
    int maxTree[4*maxN], leftTree[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];

    long long sum(int l, int r)
    {
        return sumTree[r] - sumTree[l - 1];
    }

    int findMax(int node, int l, int r)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return 0;
        }
        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            return maxTree[node];
        }

        return max(findMax(2*node, l, r), findMax(2*node + 1, l, r));
    }

    int findFirstBigger(int l, int r, int val, int node)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return r + 1;
        }

        if (maxTree[node] <= val)
        {
            return r + 1;
        }

        if (lowerIndex[node] == higherIndex[node])
        {
            return lowerIndex[node];
        }

        int firstBigger = findFirstBigger(l, r, val, 2*node);
        if (firstBigger == r + 1)
        {
            firstBigger = findFirstBigger(l, r, val, 2*node + 1);
        }

        return firstBigger;
    }

    long long query(int l, int r, int lMax = 0, int node = 1)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return 0;
        }

        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            if (lowerIndex[node] == higherIndex[node])
            {
                return max(0ll, lMax - sum(lowerIndex[node], lowerIndex[node]));
            }

            if (leftTree[node] >= lMax)
            {
                return countTree[node];
            }
        }

        int curL = max(l, lowerIndex[node]);
        int curR = min(r, higherIndex[node]);

        int idxOfBigger = findFirstBigger(curL, curR, lMax, node);
        long long lCount = idxOfBigger > curL ? (idxOfBigger - curL) * (long long)lMax - sum(curL, idxOfBigger - 1) : 0;
        long long rCount = 0;
        
        if (idxOfBigger <= curR)
        {
            if (idxOfBigger <= lowerIndex[2*node + 1])
            {
                if (idxOfBigger <= higherIndex[2*node])
                {
                    rCount += query(idxOfBigger, min(curR, higherIndex[2*node]), 0, 2*node);
                }

                if (curR >= lowerIndex[2*node + 1])
                {
                    rCount += query(lowerIndex[2*node + 1], curR, findMax(2*node, idxOfBigger, higherIndex[2*node]), 2*node + 1);
                }
            }
            else
            {
                rCount += query(idxOfBigger, curR, 0, 2*node + 1);
            }
        }

        return lCount + rCount;
    }

    void pull(int node)
    {
        maxTree[node] = max(maxTree[2*node], maxTree[2*node + 1]);
        leftTree[node] = leftTree[2*node];
        countTree[node] = countTree[2*node] + query(lowerIndex[2*node + 1], higherIndex[2*node + 1], maxTree[2*node], 2*node + 1);
    }

    void init(int node = 1, int l = 1, int r = N, int lMax = 0)
    {
        lowerIndex[node] = l;
        higherIndex[node] = r;

        if (l == r)
        {
            indexToNode[l] = node;

            int val = 0;
            scanf("%d", &val);

            sumTree[l] = val + sumTree[l-1];
            maxTree[node] = val;
            countTree[node] = 0;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m, 0);
        init(2*node + 1, m + 1, r, maxTree[2*node]);

        pull(node);
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
            printf("%lld ", countTree[node]);
        }
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        //printTree();
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            long long count = query(a, b);

            printf("%lld\n", count);
        }
    }
}

namespace solve2
{
    const int maxN = 2e5;
    long long prefSum[maxN + 1], sumTree[4*maxN];
    int maxTree[4*maxN], lazyPropagation[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];
    vector<array<int, 2>> queries[maxN + 1];

    long long srcSum(int l, int r)
    {
        return prefSum[r] - prefSum[l - 1];
    }

    void pull(int node)
    {
        maxTree[node] = max(maxTree[2*node], maxTree[2*node + 1]);
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
    }

    void assign(int node, int val)
    {
        lazyPropagation[node] = val;
        maxTree[node] = val;
        sumTree[node] = (higherIndex[node] - lowerIndex[node] + 1) * (long long)val;
    }

    void push(int node)
    {
        if (lazyPropagation[node])
        {
            assign(2*node, lazyPropagation[node]);
            assign(2*node + 1, lazyPropagation[node]);
            lazyPropagation[node] = 0;
        }
    }

    int findFirstNotLess(int l, int val, int node = 1)
    {
        if (lowerIndex[node] == higherIndex[node] || lazyPropagation[node] >= val)
        {
            return lowerIndex[node];
        }

        if (l >= higherIndex[2*node] || val > maxTree[2*node])
        {
            return findFirstNotLess(l, val, 2*node + 1);
        }
        else
        {
            return findFirstNotLess(l, val, 2*node);
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

            prefSum[l] = val + prefSum[l-1];
            sumTree[node] = val;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    void update(int l, int r, int val, int node = 1)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return;
        }

        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            assign(node, val);
            return;
        }

        push(node);
        update(l, r, val, 2*node);
        update(l, r, val, 2*node + 1);
        pull(node);
    }

    void printTree()
    {
        //return;

        int treeWidth = 1;
        while (treeWidth < N) treeWidth <<= 1;

        for (int node = 1; node < 2*treeWidth; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%lld ", sumTree[node]);
        }
        printf("\n");
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        //printTree();

        vector<long long> res(Q + 1);
        
        for (int i = 1; i <= Q; i++)
        {
            int l = 0, r = 0;
            scanf("%d%d", &l, &r);

            queries[l].push_back({r, i});
        }

        for (int l = N; l > 0; l--)
        {
            long long val = srcSum(l, l);
            int r = (val > maxTree[1]) ? N : (findFirstNotLess(l, val) - 1);
            update(l, r, val);

            //printTree();

            for(auto &q : queries[l])
            {
                res[q[1]] = querySum(l, q[0]) - srcSum(l, q[0]);
            }
        }

        for (int i = 1; i <= Q; i++)
        {
            printf("%lld\n", res[i]);
        }
    }
}

namespace solve3
{
    const int maxN = 2e5;
    long long prefSum[maxN + 1], sumTree[4*maxN];
    int lazyPropagation[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];
    vector<array<int, 2>> queries[maxN + 1];

    long long srcSum(int l, int r)
    {
        return prefSum[r] - prefSum[l - 1];
    }

    void pull(int node)
    {
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
    }

    void assign(int node, int val)
    {
        lazyPropagation[node] = val;
        sumTree[node] = (higherIndex[node] - lowerIndex[node] + 1) * (long long)val;
    }

    void push(int node)
    {
        if (lazyPropagation[node])
        {
            assign(2*node, lazyPropagation[node]);
            assign(2*node + 1, lazyPropagation[node]);
            lazyPropagation[node] = 0;
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

            prefSum[l] = val + prefSum[l-1];
            sumTree[node] = val;

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    void update(int l, int r, int val, int node = 1)
    {
        if (r < lowerIndex[node] || l > higherIndex[node])
        {
            return;
        }

        if (l <= lowerIndex[node] && r >= higherIndex[node])
        {
            assign(node, val);
            return;
        }

        push(node);
        update(l, r, val, 2*node);
        update(l, r, val, 2*node + 1);
        pull(node);
    }

    void printTree()
    {
        //return;

        int treeWidth = 1;
        while (treeWidth < N) treeWidth <<= 1;

        for (int node = 1; node < 2*treeWidth; node++)
        {
            if ((node&(node-1)) == 0)
            {
                printf("\n");
            }
            printf("%lld ", sumTree[node]);
        }
        printf("\n");
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        init();

        //printTree();

        vector<long long> res(Q + 1);
        
        for (int i = 1; i <= Q; i++)
        {
            int l = 0, r = 0;
            scanf("%d%d", &l, &r);

            queries[l].push_back({r, i});
        }

        stack<int> s;

        for (int l = N; l > 0; l--)
        {
            long long val = srcSum(l, l);
            while (!s.empty() && srcSum(s.top(), s.top()) < val)
            {
                s.pop();
            }
            int r = s.empty() ? N : (s.top() - 1);
            s.push(l);

            update(l, r, val);

            //printTree();

            for(auto &q : queries[l])
            {
                res[q[1]] = querySum(l, q[0]) - srcSum(l, q[0]);
            }
        }

        for (int i = 1; i <= Q; i++)
        {
            printf("%lld\n", res[i]);
        }
    }
}

namespace solve4
{
    const int maxN = 2e5;
    const int log2MaxN = ceil(log2(maxN));
    int nextTable[maxN + 2][log2MaxN], arr[maxN + 1];
    long long sumTable[maxN + 2][log2MaxN], prefSum[maxN + 1];
    int N, Q, log2N;

    long long query(int l, int r)
    {
        long long sum = 0;
        for (int pow = log2N - 1; pow >= 0; pow--)
        {
            if (nextTable[l][pow] != -1 && nextTable[l][pow] <= r)
            {
                sum += sumTable[l][pow];
                l = nextTable[l][pow];
            }
        }

        sum += (r - l + 1) * (long long)arr[l];

        return sum;
    }

    void printTable()
    {
        printf("\narr = \n");

        for (int j = 1; j <= N; j++)
        {
            printf("%d\t", arr[j]);
        }

        printf("\n");
        printf("\nnextTable=\n");
        
        for (int i = 0; i < log2N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                printf("%d\t", nextTable[j][i]);
            }
            printf("\n");
        }

        printf("\n");
        printf("\nsumTable=\n");

        for (int i = 0; i < log2N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                printf("%lld\t", sumTable[j][i]);
            }
            printf("\n");
        }
    }

    void initTable()
    {
        stack<int> s;

        memset(nextTable, -1, sizeof(nextTable));

        for (int idx = N; idx > 0; idx--)
        {
            while (!s.empty() && arr[idx] >= arr[s.top()])
            {
                s.pop();
            }

            nextTable[idx][0] = s.empty() ? N + 1 : s.top();
            sumTable[idx][0] = (nextTable[idx][0] - idx) * (long long)arr[idx];

            s.push(idx);
        }

        for (int pow = 1; pow < log2N; pow++)
        {
            for (int idx = 1; idx <= N; idx++)
            {
                if (nextTable[idx][pow - 1] == -1)
                {
                    continue;
                }

                nextTable[idx][pow] = nextTable[nextTable[idx][pow - 1]][pow - 1];
                if (nextTable[idx][pow] != -1)
                {
                    sumTable[idx][pow] = sumTable[idx][pow - 1] + sumTable[nextTable[idx][pow - 1]][pow - 1];
                }
            }
        }

        //printTable();
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        log2N = ceil(log2(N));

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            arr[i] = val;
            prefSum[i] = prefSum[i-1] + val;
        }

        initTable();
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            long long count = query(a, b) - (prefSum[b] - prefSum[a-1]);

            printf("%lld\n", count);
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
        //solve2::solve();
        //solve3::solve();
        solve4::solve();
    }

    return 0;
}