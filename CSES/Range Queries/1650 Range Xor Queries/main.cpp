#include <iostream>
#include <bits/stdc++.h>

using namespace std;

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
};

void solve() {
    int n = 0, q = 0;
    cin >> n >> q;

    std::vector<int> values(n);

    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    DynamicRangeFuncQueries fq(values.begin(), values.end(), [](int l, int r) -> int {
        return l ^ r;
    }, 0);
    
    for (int i = 0; i < q; i++)
    {
        int a = 0, b = 0;
        cin >> a >> b;

        cout << fq.getFuncValOnRange(a-1, b-1) << endl;
    }
}

void solve2() {
    int n = 0, q = 0;
    scanf("%d %d", &n, &q);

    std::vector<int> values(n + 1);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &values[i]);
        values[i] ^= values[i - 1];
    }
    
    for (int i = 0; i < q; i++)
    {
        int a = 0, b = 0;
        scanf("%d %d", &a, &b);

        printf("%d\n", values[b] ^ values[a-1]);
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