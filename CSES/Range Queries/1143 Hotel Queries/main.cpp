#include <iostream>
#include <bits/stdc++.h>

using namespace std;

template<typename ValT = int, class CompareT = std::less<ValT>>
class DynamicRangeBetterQueries
{
    static const size_t INF = (size_t)-1;

    CompareT compare;

    std::vector<ValT> sourceData;
    std::vector<size_t> tree;

    size_t treeWidth = 0;
    size_t treeHeight = 0;

    size_t betterIndex(size_t l, size_t r) const
    {
        if (l >= sourceData.size() && r >= sourceData.size())
        {
            return INF;
        }

        if (l >= sourceData.size())
        {
            return r;
        }
        else if (r >= sourceData.size())
        {
            return l;
        }

        if (l == r)
        {
            return l;
        }

        return compare(sourceData[l], sourceData[r]) ? l : r;
    }

public:
    DynamicRangeBetterQueries(std::vector<ValT>&& data, CompareT&& cmp = CompareT()) : sourceData(data), compare(cmp)
    {
        size_t n = sourceData.size();

        if (n == 0)
        {
            return;
        }

        if (n == INF)
        {
            throw std::invalid_argument("input data is too big");
        }

        int highestBit = sizeof(size_t) * 8 - 1;
        while (highestBit)
        {
            if (n & ((size_t)1 << highestBit))
            {
                break;
            }

            highestBit--;
        }

        if (n == ((size_t)1 << highestBit))
        {
            treeHeight = highestBit;
        }
        else // n > (1 << highestBit)
        {
            treeHeight = highestBit + 1;
        }

        treeWidth = ((size_t)1 << treeHeight) / 2;

        tree.resize(treeWidth * 2);

        for (size_t i = treeWidth, j = 0; i < tree.size(); i++, j += 2)
        {
            tree[i] = betterIndex(j, j + 1);
        }

        for (int i = (int)treeHeight - 2; i >= 0; i--)
        {
            for (size_t j = ((size_t)1 << i); j < ((size_t)1 << (i + 1)); j++)
            {
                tree[j] = betterIndex(tree[j * 2], tree[j * 2 + 1]);
            }
        }
    }

    const ValT& getBestInRange(size_t l, size_t r) const
    {
        if (l > r)
        {
            throw std::invalid_argument("l > r");
        }

        if (r >= sourceData.size())
        {
            throw std::invalid_argument("r >= sourceData.size()");
        }

        if (sourceData.size() == 1)
        {
            return sourceData[0];
        }

        size_t betterIndexOnRange = INF;

        if (l % 2 == 1)
        {
            betterIndexOnRange = betterIndex(betterIndexOnRange, l);
            l++;
        }

        if (r % 2 == 0)
        {
            betterIndexOnRange = betterIndex(betterIndexOnRange, r);
            r--;
        }

        l += tree.size();
        r += tree.size();

        while (l < r)
        {
            l /= 2;
            r /= 2;

            if (l % 2 == 1)
            {
                betterIndexOnRange = betterIndex(betterIndexOnRange, tree[l]);
                l++;
            }
    
            if (r % 2 == 0)
            {
                betterIndexOnRange = betterIndex(betterIndexOnRange, tree[r]);
                r--;
            }
        }

        return sourceData[betterIndexOnRange];
    }

    template<typename T>
    void update(size_t k, T&& x) {
        if (k >= sourceData.size())
        {
            throw std::invalid_argument("k >= sourceData.size()");
        }

        sourceData[k] = std::move(x);

        if (tree.size() == 0)
        {
            return;
        }
        
        k += tree.size();
        k /= 2;
        tree[k] = betterIndex(2*k - tree.size(), 2*k - tree.size() + 1);

        while (k >= 2)
        {
            k /= 2;
            tree[k] = betterIndex(tree[2*k], tree[2*k + 1]);
        }
    }

    int orderSuitableHotel(int request)
    {
        if (sourceData.size() == 0)
        {
            return -1;
        }

        if (sourceData.size() == 1)
        {
            return sourceData[0] >= request ? 0 : -1;
        }

        if (sourceData[tree[1]] < request)
        {
            return -1;
        }

        int index = 1;
        while(2*index < tree.size())
        {
            if (sourceData[tree[2*index]] >= request)
            {
                index = 2*index;
            }
            else
            {
                index = 2*index + 1;
            }
        }

        int res = sourceData[2*index - tree.size()] >= request ? 2*index - tree.size() : 2*index - tree.size() + 1;

        update(res, sourceData[res] - request);

        return res;
    }
};

const int maxN = 2e5;

void solve() {
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);

    std::vector<int> hotelsCapacity(n + 1);

    for (int i = 1; i <= n; i++)
    {
        int rooms = 0;
        scanf("%d", &rooms);
        
        hotelsCapacity[i] = rooms;
    }

    DynamicRangeBetterQueries<int, greater<int>> drq(std::move(hotelsCapacity));
    
    for (int i = 0; i < m; i++)
    {
        int request = 0;
        scanf("%d", &request);

        int l = 1, r = n;

        int res = drq.orderSuitableHotel(request);

        res = res == -1 ? 0 : res;
        
        printf("%d ", res);
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
        solve();
    }

    return 0;
}