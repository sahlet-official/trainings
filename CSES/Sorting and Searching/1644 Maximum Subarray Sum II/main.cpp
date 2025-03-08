#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

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

const int maxN = 2 * 1e5;
int n = 0, a = 0, b = 0;
 
void solve() {
    scanf("%d%d%d", &n, &a, &b);

    std::vector<long long> prefSum(maxN + 1);
 
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        prefSum[i] = val + prefSum[i - 1];
    }

    StaticRangeBetterQueries<long long> srq(std::move(prefSum));

    long long res = LLONG_MIN;

    for (int i = a; i <= n; i++)
    {
        long long subRes =
            srq.getBestInRange(i, i) - srq.getBestInRange(max(0, i - b), i - a);

        res = max(res, subRes);
    }

    printf("%lld", res);
}

void solve2() {
    scanf("%d%d%d", &n, &a, &b);

    std::vector<long long> prefSum(maxN + 1);
 
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        prefSum[i] = val + prefSum[i - 1];
    }

    multiset<long long> ms;

    long long res = LLONG_MIN;

    for (int i = a; i <= n; i++)
    {
        ms.insert(prefSum[i - a]);
        if (i > b)
        {
            ms.erase(ms.find(prefSum[i - b - 1]));
        }

        long long subRes = prefSum[i] - *ms.begin();
        res = max(res, subRes);
    }

    printf("%lld", res);
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