#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// search for sum in range
template<typename SumT = long long>
class BinaryIndexedTree
{
    std::vector<SumT> tree;

    template<typename _RandomAccessIterator>
    void init(const _RandomAccessIterator& begin, const _RandomAccessIterator& end)
    {
        size_t n = end - begin;
        tree.resize(n + 1);

        std::vector<SumT> prefixSum;
        prefixSum.reserve(n + 1);
        prefixSum.push_back(0);

        for (int i = 0; i < n; i++)
        {
            prefixSum.push_back(prefixSum.back() + *(begin + i));
        }

        for (int i = 1; i <= n; i++)
        {
            tree[i] = prefixSum[i] - prefixSum[i - (i&-i)];
        }
    }

public:
    template<typename RandomAccessIterator>
    BinaryIndexedTree(const RandomAccessIterator& begin, const RandomAccessIterator& end)
    {
        init(begin, end);
    }

    template<typename ValT>
    BinaryIndexedTree(const ValT* begin, const ValT* end)
    {
        init(begin, end);
    }

    SumT getRangeSum(size_t l, size_t r)
    {
        SumT sum = 0;
    
        r += 1;
    
        while (r)
        {   
            sum += tree[r];
            r -= r & (-r);
        }
    
        while (l)
        {   
            sum -= tree[l];
            l -= l & (-l);
        }
        return sum;
    }

    template<typename ValT>
    void add(size_t index, ValT val)
    {
        index = index + 1;
    
        while (index < tree.size())
        {
            tree[index] += val;
            index += index & (-index);
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

    BinaryIndexedTree rangeSum(values.begin(), values.end());
    
    for (int i = 0; i < q; i++)
    {
        int t = 0, a = 0, b = 0;
        cin >> t >> a >> b;

        if (t == 1)
        {
            rangeSum.add(a - 1, b - values[a - 1]);
            values[a - 1] = b;
        }
        else if (t == 2)
        {
            cout << rangeSum.getRangeSum(a-1, b-1) << endl;
        }
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

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}