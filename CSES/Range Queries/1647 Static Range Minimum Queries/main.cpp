#include <iostream>
#include <bits/stdc++.h>

using namespace std;

template<typename ValT = int>
class StaticRangeMinQueries
{
    std::vector<std::vector<ValT>> memory;

    template<typename _RandomAccessIterator>
    void init(const _RandomAccessIterator& begin, const _RandomAccessIterator& end)
    {
        size_t n = end - begin;
        size_t memoryRowsNumber = (size_t)std::log2(n) + 1;
        memory.resize(memoryRowsNumber);

        memory[0].resize(n);
        for (size_t i = 0; i < memory[0].size(); i++)
        {
            memory[0][i] = *(begin + i);
        }

        size_t rangeSize = 1;

        for (size_t i = 1; i < memoryRowsNumber; i++)
        {
            rangeSize *= 2;
            
            memory[i].resize(n - (rangeSize - 1));

            for (size_t j = 0; j < memory[i].size(); j++)
            {
                memory[i][j] = std::min(memory[i - 1][j], memory[i - 1][j + rangeSize / 2]);
            }
        }
    }

public:
    template<typename RandomAccessIterator>
    StaticRangeMinQueries(const RandomAccessIterator& begin, const RandomAccessIterator& end)
    {
        init(begin, end);
    }

    template<typename ValT>
    StaticRangeMinQueries(const ValT* begin, const ValT* end)
    {
        init(begin, end);
    }

    ValT getRangeMin(size_t l, size_t r)
    {
        
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

    StaticRangeMinQueries mq(values.begin(), values.end());
    
    for (int i = 0; i < q; i++)
    {
        int a = 0, b = 0;
        cin >> a >> b;

        a--;
        b--;

        cout << mq.getRangeMin(a, b) << endl;
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