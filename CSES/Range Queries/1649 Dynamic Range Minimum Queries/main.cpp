#include <iostream>
#include <bits/stdc++.h>

using namespace std;

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
    DynamicRangeBetterQueries(std::vector<ValT>&& data, CompareT&& cmp = std::less<ValT>()) : sourceData(data), compare(cmp)
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

void solve() {
    int n = 0, q = 0;
    cin >> n >> q;

    std::vector<int> values(n);

    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    DynamicRangeBetterQueries bq(std::move(values));
    
    for (int i = 0; i < q; i++)
    {
        int t = 0, a = 0, b = 0;
        cin >> t >> a >> b;

        if (t == 1)
        {
            bq.update(a - 1, b);
        }
        else if (t == 2)
        {
            cout << bq.getBestInRange(a-1, b-1) << endl;
        }
    }
}


const int maxN = 2e5;
const int SIZE = 2*2*maxN;
const int INF = INT_MAX;
int tree[SIZE];
int leftIndex[SIZE], rightIndex[SIZE];

int n = 0, q = 0;

void pull(int node)
{
    tree[node] = min(tree[2*node], tree[2*node + 1]);
}

void init(int node, int l, int r)
{
    leftIndex[node] = l;
    rightIndex[node] = r;

    if (l == r)
    {
        //scanf("%d", &tree[node]);
        cin >> tree[node];
        return;
    }

    int mid = l + (r - l) / 2;

    init(2*node, l, mid);
    init(2*node + 1, mid + 1, r);
    pull(node);
}

void update(int node, int index, int val)
{
    if (leftIndex[node] > index || rightIndex[node] < index)
    {
        return;
    }

    if (leftIndex[node] == rightIndex[node])
    {
        tree[node] = val;
    }
    else
    {
        update(2*node, index, val);
        update(2*node + 1, index, val);
        pull(node);
    }
}

int getMinOnRange(int node, int l, int r)
{
    if (leftIndex[node] > r || rightIndex[node] < l)
    {
        return INF;
    }

    if (l <= leftIndex[node] && r >= rightIndex[node])
    {
        return tree[node];
    }

    return min(getMinOnRange(2*node, l, r), getMinOnRange(2*node + 1, l, r));
}

void solve2() {
    cin >> n >> q;
    //scanf("%d %d", &n, &q);

    init(1, 1, n);
    
    for (int i = 0; i < q; i++)
    {
        int t = 0, a = 0, b = 0;
        cin >> t >> a >> b;
        //scanf("%d %d %d", &t, &a, &b);

        if (t == 1)
        {
            update(1, a, b);
        }
        else if (t == 2)
        {
            printf("%d\n", getMinOnRange(1, a, b));
            //cout << getMinOnRange(1, a, b) << endl;
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
        solve2();
    }

    return 0;
}