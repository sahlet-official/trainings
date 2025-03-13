#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    long long sumTree[4*maxN], maxPrefixSumTree[4*maxN], maxSuffixSumTree[4*maxN], maxSubArrSum[4*maxN];
    int N, Q, lowerIndex[4*maxN], higherIndex[4*maxN], indexToNode[maxN + 1];

    void pull(int node)
    {
        sumTree[node] = sumTree[2*node] + sumTree[2*node + 1];
        maxPrefixSumTree[node] = max(maxPrefixSumTree[2*node], sumTree[2*node] + maxPrefixSumTree[2*node + 1]);
        maxSuffixSumTree[node] = max(maxSuffixSumTree[2*node] + sumTree[2*node + 1], maxSuffixSumTree[2*node + 1]);
        maxSubArrSum[node] = max(max(maxSubArrSum[2*node], maxSubArrSum[2*node + 1]), maxSuffixSumTree[2*node] + maxPrefixSumTree[2*node + 1]);
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
            maxPrefixSumTree[node] = max(val, 0);
            maxSuffixSumTree[node] = max(val, 0);
            maxSubArrSum[node] = max(val, 0);

            return;
        }

        int m = (l + r) / 2;
        init(2*node, l, m);
        init(2*node + 1, m + 1, r);

        pull(node);
    }

    long long query()
    {
        return maxSubArrSum[1];
    }

    void update(int idx, int val)
    {
        int node = indexToNode[idx];

        sumTree[node] = val;
        maxPrefixSumTree[node] = max(val, 0);
        maxSuffixSumTree[node] = max(val, 0);
        maxSubArrSum[node] = max(val, 0);

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
            int idx = 0, val = 0;
            scanf("%d%d", &idx, &val);

            update(idx, val);
            long long maxSubArr = query();
            printf("%lld\n", maxSubArr);
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
        solve1::solve();
    }

    return 0;
}