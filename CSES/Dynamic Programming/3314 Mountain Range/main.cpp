#include <iostream>
#include <bits/stdc++.h>

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

using namespace std;

namespace Solution1 {
    const int maxN = (int)2e5;
    int mountainHeights[maxN];
    std::pair<int, int> sortedHeights[maxN];
    std::pair<int, int> allowedMountainRanges[maxN];
    int n = 0;

    void determineAllowedMountainLeftLimit() {
        std::stack<int> nearestBiggerValues;

        for (int i = 0; i < n; i++) {
            while (!nearestBiggerValues.empty() && mountainHeights[i] > mountainHeights[nearestBiggerValues.top()]) {
                nearestBiggerValues.pop();
            }

            if (!nearestBiggerValues.empty()) {
                allowedMountainRanges[i].first = nearestBiggerValues.top() + 1;
            } else {
                allowedMountainRanges[i].first = 0;
            }   

            nearestBiggerValues.push(i);
        }
    }

    void determineAllowedMountainRightLimit() {
        std::stack<int> nearestBiggerValues;

        for (int i = n-1; i >= 0; i--) {
            while (!nearestBiggerValues.empty() && mountainHeights[i] > mountainHeights[nearestBiggerValues.top()]) {
                nearestBiggerValues.pop();
            }

            if (!nearestBiggerValues.empty()) {
                allowedMountainRanges[i].second = nearestBiggerValues.top() - 1;
            } else {
                allowedMountainRanges[i].second = n-1;
            }   

            nearestBiggerValues.push(i);
        }
    }

    void determineAllowedMountainRanges() {
        determineAllowedMountainLeftLimit();
        determineAllowedMountainRightLimit();
    }

    void solve() {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &mountainHeights[i]);
            sortedHeights[i] = {mountainHeights[i], i};
        }

        std::sort(sortedHeights, sortedHeights + n);

        determineAllowedMountainRanges();

        std::vector<int> BITSrcData(n);
        DynamicRangeBetterQueries<int, std::greater<int>> BIT(std::move(BITSrcData));

        int res = 0;

        for (int i = 0; i < n; i++) {
            auto range = allowedMountainRanges[sortedHeights[i].second];
            int subres = 1 + BIT.getBestInRange(range.first, range.second);
            res = max(res, subres);

            BIT.update(sortedHeights[i].second, subres);
        }

        printf("%d\n", res);
    }
}

namespace Solution2_NotMy {
    typedef pair<int,int> pii;
    const int maxN = 2e5+1;
    const int INF = 0x3f3f3f3f;

    int N, dp[maxN];
    vector<int> tallers;
    vector<pii> mountains;
    set<int,greater<int>> S_l;
    set<int> S_r;

    void solve() {
        scanf("%d", &N);

        for(int i = 1, h; i <= N; i++){
            scanf("%d", &h);
            mountains.push_back({h, i});
        }
        sort(mountains.begin(), mountains.end(), greater<pii>());

        int last_height = INF;
        for(pii m : mountains){
            int h = m.first, i = m.second;

            if(last_height != h){
                for(int t : tallers){
                    S_l.insert(t);
                    S_r.insert(t);
                }
                tallers.clear();
            }

            auto l_ptr = S_l.lower_bound(i);
            auto r_ptr = S_r.lower_bound(i);
            int l = (l_ptr == S_l.end() ? 0 : *l_ptr);
            int r = (r_ptr == S_r.end() ? 0 : *r_ptr);
            dp[i] = max(dp[l], dp[r]) + 1;

            tallers.push_back(i);
            last_height = h;
        }

        int best = 0;
        for(int i = 1; i <= N; i++)
            best = max(best, dp[i]);
        printf("%d\n", best);
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
        // Solution2_NotMy::solve();
    }

    return 0;
}