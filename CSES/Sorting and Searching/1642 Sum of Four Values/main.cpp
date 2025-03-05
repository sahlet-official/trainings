#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 1000;
int n, x;
pair<int, int> values[maxN + 1];

void solve() {
    scanf("%d%d", &n, &x);
 
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        values[i] = {val, i};
    }

    sort(values + 1, values + n + 1);

    for (int j = 1; j <= n; j++)
    {
        for (int i = j + 1; i <= n; i++)
        {
            int sum = x - values[i].first - values[j].first;
            
            int l = i + 1;
            int r = n;
            
            for (; l < r; l++)
            {
                int target = sum - values[l].first;

                while(l < r && target < values[r].first)
                {
                    r--;
                }

                if (l < r && target == values[r].first)
                {
                    printf("%d %d %d %d", values[j].second, values[i].second, values[l].second, values[r].second);
                    return;
                }
            }
        }
    }

    printf("IMPOSSIBLE");
}

void solve2() {
    scanf("%d%d", &n, &x);

    unordered_map<int, vector<pair<int, int>>> twoSumMemory;

    for (int j = 1; j <= n; j++)
    {
        int val = 0;
        scanf("%d", &val);

        values[j] = {val, j};

        for (int i = 1; i < j; i++)
        {
            int lSum = values[i].first + values[j].first;
            int rSum = x - lSum;

            auto iter = twoSumMemory.find(rSum);

            if (iter != twoSumMemory.end())
            {
                for (auto& p : iter->second)
                {
                    if (p.first != i && p.second != i && p.first != j && p.second != j)
                    {
                        printf("%d %d %d %d", p.first, p.second, i, j);
                        return;
                    }
                }
            }

            twoSumMemory[lSum].push_back({i, j});
        }
    }

    printf("IMPOSSIBLE");
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
        solve2();
    }
 
    return 0;
}