#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 2e5;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n = 0;
    scanf("%d", &n);
    
    ordered_set<pair<int, int>> orderedSet;

    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);
        orderedSet.insert({i, val});
    }
    
    for (int i = 1; i <= n; i++)
    {
        int order = 0;
        scanf("%d", &order);
        auto iter = orderedSet.find_by_order(order - 1);

        int val = iter->second;

        orderedSet.erase(iter);
        
        printf("%d ", val);
    }
}

int orderTree[4*maxN];
int arr[maxN];
int n = 0;
int treeWidth = 0;

void init()
{
    treeWidth = 1;
    while (treeWidth < n) treeWidth <<= 1;

    for(int node = 0; node < n; node++)
    {
        orderTree[node + treeWidth] = 1;
    }

    for(int node = treeWidth - 1; node > 0; node--)
    {
        orderTree[node] = orderTree[2*node] + orderTree[2*node + 1];
    }
}

int findIndexByOrder(int order)
{
    int node = 1;

    if (orderTree[node] < order)
    {
        return -1;
    }

    while (node < treeWidth)
    {
        if (orderTree[2*node] >= order)
        {
            node = 2*node;
        }
        else
        {
            order -= orderTree[2*node];
            node = 2*node + 1;
        }
    }
    
    return node - treeWidth;
}

void erase(int index) {
    index += treeWidth;

    orderTree[index] = 0;

    while (index >= 2)
    {
        index /= 2;
        orderTree[index] = orderTree[2*index] + orderTree[2*index + 1];
    }
}

void solve2() {
    scanf("%d", &n);

    init();

    for (int i = 0; i < n; i++)
    {
        int val = 0;
        scanf("%d", &val);
        arr[i] = val;
    }
    
    for (int i = 0; i < n; i++)
    {
        int order = 0;
        scanf("%d", &order);
        int index = findIndexByOrder(order);

        erase(index);
        
        printf("%d ", arr[index]);
    }
}

void pull(int node)
{
    orderTree[node] = orderTree[2*node] + orderTree[2*node + 1];
}

void init2(int node = 1, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        orderTree[node] = 1;
        return;
    }

    int m = (l + r) / 2;

    init2(2*node, l, m);
    init2(2*node + 1, m + 1, r);
    pull(node);
}

int findIndexByOrder2AndErase(int order, int node = 1, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        if (order == 1)
        {
            orderTree[node] = 0;
            return l;
        }

        return -1;
    }

    int m = (l + r) / 2;

    if (orderTree[2*node] >= order)
    {
        int res = findIndexByOrder2AndErase(order, 2*node, l, m);
        pull(node);
        return res;
    }
    else
    {
        int res = findIndexByOrder2AndErase(order - orderTree[2*node], 2*node + 1, m + 1, r);
        pull(node);
        return res;
    }
}

void solve3() {
    scanf("%d", &n);

    init2();

    for (int i = 0; i < n; i++)
    {
        int val = 0;
        scanf("%d", &val);
        arr[i] = val;
    }
    
    for (int i = 0; i < n; i++)
    {
        int order = 0;
        scanf("%d", &order);
        int index = findIndexByOrder2AndErase(order);
        
        printf("%d ", arr[index]);
    }
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

void solve4() {
    scanf("%d", &n);

    vector<int> initVals(n, 1);

    DynamicRangeFuncQueries drq(
        initVals.begin(), initVals.end(), [](int l, int r)
        {
            return l + r;
        },
        0
    );

    for (int i = 0; i < n; i++)
    {
        int val = 0;
        scanf("%d", &val);
        arr[i] = val;
    }
    
    for (int i = 0; i < n; i++)
    {
        int order = 0;
        scanf("%d", &order);
        
        int index = drq.findIndex([&](int l, int r) -> bool
        {
            if(l >= order)
            {
                return true;
            }
            else
            {
                order -= l;
                return false;
            }
        });

        drq.update(index, 0);
        
        printf("%d ", arr[index]);
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
        solve2();
    }

    return 0;
}