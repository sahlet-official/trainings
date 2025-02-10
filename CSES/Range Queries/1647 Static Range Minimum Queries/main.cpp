#include <iostream>
#include <bits/stdc++.h>

using namespace std;

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

void solve() {
    int n = 0, q = 0;
    cin >> n >> q;

    std::vector<int> values(n);

    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    StaticRangeBetterQueries mq(std::move(values));
    
    for (int i = 0; i < q; i++)
    {
        int a = 0, b = 0;
        cin >> a >> b;

        a--;
        b--;

        cout << mq.getBestInRange(a, b) << endl;
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