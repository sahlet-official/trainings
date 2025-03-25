#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // lowest common ancestor
{
    const int maxN = 2e5;
    const int maxJumps = ceil(log2(maxN)) - 1;
    vector<int> children[maxN + 1];
    int bosses[maxN + 1][maxJumps + 1];
    int depth[maxN + 1];
    int N, Q;

    int processQuery(int employee1, int employee2)
    {
        if (depth[employee1] < depth[employee2])
        {
            swap(employee1, employee2);
        }

        int steps = depth[employee1] - depth[employee2];

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (steps & (1 << jump))
            {
                employee1 = bosses[employee1][jump];
            }
        }

        if (employee1 == employee2)
        {
            return employee1;
        }

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (bosses[employee1][jump] != bosses[employee2][jump])
            {
                employee1 = bosses[employee1][jump];
                employee2 = bosses[employee2][jump];
            }
        }
        
        return bosses[employee1][0];
    }

    void dfs(int node = 1, int d = 0)
    {
        depth[node] = d;

        for (int childe : children[node])
        {
            dfs(childe, d + 1);
        }
    }

    void init()
    {
        dfs();
        for (int jump = 1; jump <= maxJumps; jump++)
        {
            for (int i = 1; i <= N; i++)
            {
                if (bosses[i][jump - 1] == -1)
                {
                    bosses[i][jump] = -1;
                    continue;
                }

                bosses[i][jump] = bosses[bosses[i][jump - 1]][jump - 1];
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        bosses[1][0] = -1;

        for (int i = 2; i <= N; i++)
        {
            int boss = 0;
            scanf("%d", &boss);

            bosses[i][0] = boss;
            children[boss].push_back(i);
        }

        init();

        for (int i = 1; i <= Q; i++)
        {
            int employee = 0, steps = 0;
            scanf("%d%d", &employee, &steps);
            printf("%d\n", processQuery(employee, steps));
        }
    }
}

namespace solve2 // lowest common ancestor by min query
{
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

    size_t getBestInRange(size_t l, size_t r) const
    {
        if (l > r)
        {
            swap(l, r);
        }

        size_t rangeLength = r - l + 1;
        if (rangeLength == 1)
        {
            return l;
        }

        size_t memoryRow = (size_t)std::log2(rangeLength) - 1;
        size_t queryRangeSize = 1 << (memoryRow + 1);

        return betterIndex(memory[memoryRow][l], memory[memoryRow][r + 1 - queryRangeSize]);
    }
};

    const int maxN = 2e5;
    vector<int> children[maxN + 1];
    vector<int> idToDepth;
    int nodeToId[maxN + 1];
    vector<int> idToNode;
    StaticRangeBetterQueries<int, std::less<int>> minQueries({});
    int N, Q;

    int processQuery(int employee1, int employee2)
    {
        int lcaId = minQueries.getBestInRange(nodeToId[employee1], nodeToId[employee2]);
        
        return idToNode[lcaId];
    }

    int id = 0;

    void dfs(int node = 1, int d = 0)
    {
        nodeToId[node] = id;
        
        idToDepth.push_back(d);
        idToNode.push_back(node);
        id++;

        for (int childe : children[node])
        {
            dfs(childe, d + 1);
            idToDepth.push_back(d);
            idToNode.push_back(node);
            id++;
        }
    }

    void init()
    {
        dfs();
        
        minQueries = StaticRangeBetterQueries<int, std::less<int>>(std::move(idToDepth));
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        for (int i = 2; i <= N; i++)
        {
            int boss = 0;
            scanf("%d", &boss);

            children[boss].push_back(i);
        }

        init();

        for (int i = 1; i <= Q; i++)
        {
            int employee = 0, steps = 0;
            scanf("%d%d", &employee, &steps);
            printf("%d\n", processQuery(employee, steps));
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
        //solve1::solve();
        solve2::solve();
    }

    return 0;
}