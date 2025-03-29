#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
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

    BinaryIndexedTree()
    {
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


    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int dfsTraversal[maxN + 1];
    int subtreeSize[maxN + 1];
    int vals[maxN + 1];
    long long pathSums[maxN + 1];
    long long sumsDFSOrder[maxN + 1];
    long long sumsDifs[maxN + 1];
    BinaryIndexedTree<long long> BIT;
    int N, Q;

    int order = 1;
    void dfs(int node = 1, int parent = 1)
    {
        pathSums[node] = vals[node] + pathSums[parent];
        dfsTraversal[node] = order;
        order++;
        subtreeSize[node] = 1;
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) {
                dfs(neighbor, node);
                subtreeSize[node] += subtreeSize[neighbor];
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            vals[i] = val;
        }

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        dfs();

        for (int i = 1; i <= N; i++)
        {
            sumsDFSOrder[dfsTraversal[i]] = pathSums[i];
        }

        long long prevSum = 0, curSum = 0;
        for (int i = 1; i <= N; i++)
        {
            prevSum = curSum;
            curSum = sumsDFSOrder[i];
            sumsDifs[i] = curSum - prevSum;
        }

        BIT = BinaryIndexedTree(sumsDifs, sumsDifs + N + 1);

        for (int i = 1; i <= Q; i++)
        {
            int t = 0, b = 0;
            scanf("%d", &t);
            
            if (t == 1)
            {
                int node = 0, val = 0;
                scanf("%d%d", &node, &val);
                
                int oldVal = vals[node];
                vals[node] = val;

                BIT.add(dfsTraversal[node], val - oldVal);
                BIT.add(dfsTraversal[node] + subtreeSize[node], oldVal - val);
            }
            else if (t == 2)
            {
                int node = 0;
                scanf("%d", &node);
                
                printf("%lld\n", BIT.getRangeSum(1, dfsTraversal[node]));
            }
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve();
        //solve2::solve();
    }

    return 0;
}