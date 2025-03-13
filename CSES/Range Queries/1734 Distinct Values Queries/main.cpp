#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    int BIT[maxN + 1], arr[maxN + 1], ptr[maxN + 1];
    unordered_map<int, int> valToIdx;
    unordered_set<int> itWas;
    array<int, 3> queries[maxN + 1];
    int res[maxN + 1];
    int N, Q;

    void update(int idx, int val)
    {
        for (int i = idx; i <= N; i += i&-i)
        {
            BIT[i] += val;
        }
    }

    int query(int idx)
    {
        int sum = 0;
        for (int i = idx; i >= 1; i -= i&-i)
        {
            sum += BIT[i];
        }

        return sum;
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            arr[i] = val;
            
            if(itWas.count(val) == 0)
            {
                update(i, 1);
                itWas.insert(val);
            }
        }

        for (int i = N; i >= 1; i--)
        {
            if (valToIdx.count(arr[i]))
            {
                ptr[i] = valToIdx[arr[i]];
            }

            valToIdx[arr[i]] = i;
        }
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            queries[i] = {a, b, i};
        }

        sort(queries + 1, queries + Q + 1);

        int l = 1;

        for (int i = 1; i <= Q; i++)
        {
            while (l < queries[i][0])
            {
                if (ptr[l])
                {
                    update(ptr[l], 1);
                }
                l++;
            }

            res[queries[i][2]] = query(queries[i][1]) - query(queries[i][0] - 1);
        }

        for (int i = 1; i <= Q; i++)
        {
            printf("%d\n", res[i]);
        }
    }
}

namespace solve2
{
    const int maxN = 2e5;
    int BIT[maxN + 1], arr[maxN + 1], ptr[maxN + 1];
    unordered_map<int, int> valToIdx;
    unordered_set<int> itWas;
    vector<array<int, 2>> queries[maxN + 1];
    int res[maxN + 1];
    int N, Q;

    void update(int idx, int val)
    {
        for (int i = idx; i <= N; i += i&-i)
        {
            BIT[i] += val;
        }
    }

    int query(int idx)
    {
        int sum = 0;
        for (int i = idx; i >= 1; i -= i&-i)
        {
            sum += BIT[i];
        }

        return sum;
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            arr[i] = val;
            
            if(itWas.count(val) == 0)
            {
                update(i, 1);
                itWas.insert(val);
            }
        }

        for (int i = N; i >= 1; i--)
        {
            if (valToIdx.count(arr[i]))
            {
                ptr[i] = valToIdx[arr[i]];
            }

            valToIdx[arr[i]] = i;
        }
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            queries[a].push_back({b, i});
        }

        for (int l = 1; l <= N; l++)
        {
            for (auto& q : queries[l])
            {
                res[q[1]] = query(q[0]) - query(l - 1);
            }

            if (ptr[l])
            {
                update(ptr[l], 1);
            }
        }

        for (int i = 1; i <= Q; i++)
        {
            printf("%d\n", res[i]);
        }
    }
}

namespace solve3
{
    const int maxN = 2e5;
    int BIT[maxN + 1], arr[maxN + 1];
    unordered_map<int, int> valToIdx;
    unordered_set<int> itWas;
    vector<array<int, 2>> queries[maxN + 1];
    int res[maxN + 1];
    int N, Q;

    void update(int idx, int val)
    {
        for (int i = idx; i <= N; i += i&-i)
        {
            BIT[i] += val;
        }
    }

    int query(int idx)
    {
        int sum = 0;
        for (int i = idx; i >= 1; i -= i&-i)
        {
            sum += BIT[i];
        }

        return sum;
    }

    void solve() {
        scanf("%d%d", &N, &Q);

        for (int i = 1; i <= N; i++)
        {
            int val = 0;
            scanf("%d", &val);

            arr[i] = val;
        }
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            queries[b].push_back({a, i});
        }

        for (int r = 1; r <= N; r++)
        {
            if (valToIdx.count(arr[r]))
            {
                update(valToIdx[arr[r]], -1);
            }
            valToIdx[arr[r]] = r;

            update(r, 1);

            for (auto& q : queries[r])
            {
                res[q[1]] = query(r) - query(q[0] - 1);
            }
        }

        for (int i = 1; i <= Q; i++)
        {
            printf("%d\n", res[i]);
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
        //solve1::solve();
        //solve2::solve();
        solve3::solve();
    }

    return 0;
}