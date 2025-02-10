#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

inline long long modPow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if (b % 2)
        {
            res = modMult(res, a);
        }

        b /= 2;
        a = modMult(a, a);
    }

    return res;
}

inline long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

inline long long modDivide(long long a, long long b)
{
    a %= MOD;
    b %= MOD;
    if (a % b == 0) {
        return a / b;
    }

    return modMult(a, modInverse(b));
}

// -----------------------------------------------
// Range queries

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
    
        while (index <= n)
        {
            tree[index] += val;
            index += index & (-index);
        }
    }
};

// search for best in range
template<typename ValT = int, class CompareT = std::less<ValT>>
class StaticRangeBetterQueries
{
    CompareT compare;

    std::vector<ValT> sourceData;
    std::vector<std::vector<size_t>> memory;

    size_t betterIndex(size_t l, size_t r) const
    {
        return compare(sourceData[l], sourceData[r]) ? l : r;
    }

public:
    StaticRangeBetterQueries(std::vector<ValT>&& data, CompareT&& cmp = std::less<ValT>()) : compare(cmp), sourceData(data)
    {
        const size_t n = data.size();
        size_t memoryRowsNumber = (size_t)std::log2(n);

        if (memoryRowsNumber < 1)
        {
            return;
        }
        
        memory.resize(memoryRowsNumber);

        size_t rangeSize = 2;
            
        memory[0].resize(n - (rangeSize - 1));

        for (size_t j = 0; j < memory[0].size(); j++)
        {
            memory[0][j] = betterIndex(j, j + 1);
        }

        for (size_t i = 1; i < memoryRowsNumber; i++)
        {
            rangeSize *= 2;
            
            memory[i].resize(n - (rangeSize - 1));

            for (size_t j = 0; j < memory[i].size(); j++)
            {
                memory[i][j] = betterIndex(memory[i - 1][j], memory[i - 1][j + rangeSize / 2]);
            }
        }
    }

    const ValT& getBestInRange(size_t l, size_t r) const
    {
        if (l > r)
        {
            throw std::invalid_argument("l > r");
        }

        size_t rangeLength = r - l + 1;
        if (rangeLength == 1)
        {
            return sourceData[l];
        }

        size_t memoryRow = (size_t)std::log2(rangeLength) - 1;
        size_t queryRangeSize = 1 << (memoryRow + 1);

        return sourceData[betterIndex(memory[memoryRow][l], memory[memoryRow][r + 1 - queryRangeSize])];
    }
};

// -----------------------------------------------
// Graphs

class UnionFind {
    vector<int> rank, parent;

public:
    UnionFind(int n) {
        rank.resize(n, 0);
        parent.resize(n);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool connect(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot) {
            return false;
        }

        // Union by rank
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        }
        else if (rank[yRoot] < rank[xRoot]) {
            parent[yRoot] = xRoot;
        }
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }

        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};