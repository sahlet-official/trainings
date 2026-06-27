#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

// count func on range
// Segment Tree
template<typename ValT = int>
class DynamicRangeFuncQueries
{
    std::function<ValT (const ValT& l, const ValT& r)> func;

    ValT neutralElement;
    std::vector<ValT> tree;

    template<typename _RandomAccessIterator>
    void init(const _RandomAccessIterator& begin, const _RandomAccessIterator& end)
    {
        size_t n = end - begin;

        size_t size = 1;
        while (size < n) size *= 2;

        tree.resize(size * 2, neutralElement);

        for (int i = 0; i < n; i++)
        {
            tree[i + size] = *(begin + i);
        }

        for (size_t i = size - 1; i >= 1; i--) {
            tree[i] = func(tree[2 * i], tree[2 * i + 1]);
        }
    }

public:
    template<typename _RandomAccessIterator, typename FuncT>
    DynamicRangeFuncQueries(
        const _RandomAccessIterator& begin,
        const _RandomAccessIterator& end,
        FuncT func = std::min,
        ValT neutralElement = INT_MAX)
        : func(func), neutralElement(neutralElement)
    {
        init(begin, end);
    }

    template<typename FuncT>
    DynamicRangeFuncQueries(
        const ValT* begin,
        const ValT* end,
        FuncT func = std::min,
        ValT neutralElement = INT_MAX)
        : func(func), neutralElement(neutralElement)
    {
        init(begin, end);
    }

    ValT getFuncValOnRange(size_t l, size_t r) const
    {
        if (l > r)
        {
            throw std::invalid_argument("l > r");
        }

        if (r >= tree.size() / 2)
        {
            throw std::invalid_argument("r >= tree.size() / 2");
        }

        l += tree.size() / 2;
        r += tree.size() / 2;

        ValT res = neutralElement;

        while (l <= r)
        {
            if (l % 2 == 1)
            {
                res = func(tree[l], res);
                l++;
            }
    
            if (r % 2 == 0)
            {
                res = func(tree[r], res);
                r--;
            }

            l /= 2;
            r /= 2;
        }

        return res;
    }

    template<typename T>
    void update(size_t k, T&& x) {
        if (k >= tree.size() / 2)
        {
            throw std::invalid_argument("k >= sourceData.size()");
        }

        k += tree.size() / 2;

        tree[k] = std::move(x);

        while (k >= 2)
        {
            k /= 2;
            tree[k] = func(tree[2*k], tree[2*k + 1]);
        }
    }

    size_t findIndex(std::function<bool /*go to left*/ (const ValT& l, const ValT& r)> goToLeftPredicate)
    {
        int node = 1;

        while (node < tree.size() / 2)
        {
            if (goToLeftPredicate(tree[2*node], tree[2*node + 1]))
            {
                node = 2*node;
            }
            else
            {
                node = 2*node + 1;
            }
        }
        
        return node - tree.size() / 2;
    }
};

namespace Solution1 {
    const int maxN = (int)2e5;
    int buffer[maxN + 1];
    int increasingSubsequencesCountEndsOnIndex[maxN + 1];
    std::map<int, vector<int>> valuesAndTheirIndices;

    void solve() {
        int n = 0;

        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
        {
            int val = 0;
            scanf("%d", &val);
            valuesAndTheirIndices[val].push_back(i);
        }

        DynamicRangeFuncQueries<int> sumSegmentTree(buffer, buffer + n + 1, modSum, 0);

        sumSegmentTree.update(0, 1);

        for (auto& pair : valuesAndTheirIndices) {
            for (int index : pair.second) {
                increasingSubsequencesCountEndsOnIndex[index] = sumSegmentTree.getFuncValOnRange(0, index);
            }

            for (int index : pair.second) {
                sumSegmentTree.update(index, increasingSubsequencesCountEndsOnIndex[index]);
            }
        }

        int resCountOfIncreasingSubsequences = sumSegmentTree.getFuncValOnRange(1, n);

        printf("%d\n", resCountOfIncreasingSubsequences);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        Solution1::solve();
    }

    return 0;
}