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
        prefixSum.emplace_back(0);

        for (size_t i = 0; i < n; i++)
        {
            prefixSum.emplace_back(prefixSum.back() + *(begin + i));
        }

        for (size_t i = 1; i <= n; i++)
        {
            tree[i] = prefixSum[i] - prefixSum[i - (i&-i)];
        }
    }

public:
    template<typename _RandomAccessIterator>
    BinaryIndexedTree(const _RandomAccessIterator& begin, const _RandomAccessIterator& end)
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

        if (n == 0)
        {
            return;
        }

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

// search for best in range
// Segment Tree
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
};

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


// -----------------------------------------------
// Graphs

// Ranked UnionFind (DSU - Disjoint Set Union)
class UnionFind {
    vector<int> info;

public:
    UnionFind(int n) {
        info.resize(n, -1);
    }

    int find(int x) {
        if (info[x] < 0) return x;
        info[x] = find(info[x]);
        return info[x];
    }

    bool connect(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) {
            return false;
        }

        // Union by rank
        if (info[x] < info[y]) {
            swap(x, y);
        }

        info[x] = y;
        info[y]--;

        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

// more detailed then previous (uses more memory)
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

// -----------------------------------------------
// Trees

// Link/Cut Tree (LCT)

namespace LinkCutTree {
    struct Lazy {
        int a = 1, b = 0;
        bool empty(){ return (a == 1 && b == 0); }
    };
    
    struct Node {
        Lazy tag;
        Node* children[2] = {nullptr, nullptr};
        Node* parent = nullptr;
        bool reversed = false;
        int size, value, sum, minValue, maxValue, id;
        static int idcounter;

        Node(int val = 0) : id(++idcounter) {
            set(val);
        }
        
        void apply(Lazy other) {
            minValue = minValue * other.a + other.b;
            maxValue = maxValue * other.a + other.b;
            value = value * other.a + other.b;
            sum = sum * other.a + size * other.b;
            tag = {tag.a * other.a, tag.b * other.a + other.b};
        }

        void set(int val) {
            value = val;
            pull();
        }

        void push() {
            if (reversed) {
                swap(children[0], children[1]);
                if (children[0]) children[0]->reversed ^= true;
                if (children[1]) children[1]->reversed ^= true;
                reversed = false;
            }
            if (!tag.empty()) {
                if (children[0]) children[0]->apply(tag);
                if (children[1]) children[1]->apply(tag);
                tag = Lazy();
            }
        }

        void pull() {
            sum = minValue = maxValue = value;
            size = 1;
            for (int i = 0; i < 2; i++) {
                if (children[i]) {
                    minValue = min(minValue, children[i]->minValue);
                    maxValue = max(maxValue, children[i]->maxValue);
                    sum += children[i]->sum;
                    size += children[i]->size;
                }
            }
        }

        bool isRoot() {
            return !parent || (parent->children[0] != this && parent->children[1] != this);
        }
    };
    int Node::idcounter = 0;

    void rotate(Node *x) {
        Node *p = x->parent, *g = p->parent;
        bool isLeftChild = (p->children[0] == x);
        bool pWasRoot = p->isRoot();

        p->children[!isLeftChild] = x->children[isLeftChild];
        if (x->children[isLeftChild]) {
            x->children[isLeftChild]->parent = p;
        }
    
        x->children[isLeftChild] = p;
        p->parent = x;
    
        x->parent = g;
        if (g && !pWasRoot) {
            g->children[g->children[1] == p] = x;
        }
    
        p->pull();
        x->pull();
    }

    void splay(Node *x) {
        while (!x->isRoot()) {
            Node *p = x->parent, *g = p->parent;
            if (!p->isRoot()) g->push();
            p->push();
            x->push();
            if (!p->isRoot()) {
                bool zigZig = (g->children[0] == p) == (p->children[0] == x);
                rotate(zigZig ? p : x);
            }
            rotate(x);
        }
        x->push();
        x->pull();
    }

    Node* access(Node *x) {
        Node *last = nullptr;
        for (Node *y = x; y; y = y->parent) {
            splay(y);
            y->children[1] = last;
            y->pull();
            last = y;
        }
        splay(x);
        return last;
    }

    void evert(Node *x) {
        access(x);
        x->reversed ^= true;
    }

    void link(Node *x, Node *y) {
        evert(x);
        x->parent = y;
    }

    void cut(Node *x, Node *y) {
        evert(x);
        access(y);
        if (y->children[0]) y->children[0]->parent = nullptr;
        y->children[0] = nullptr;
        y->pull();
    }

    Node* path(Node *x, Node *y) {
        evert(x);
        access(y);
        return y;
    }

    Node* LCA(Node *x, Node *y) {
        access(x);
        return access(y);
    }

    bool connected(Node *x, Node *y) {
        path(x, y);
        while (y->children[0])
            y = y->children[0];
        return x == y;
    }
}    

