#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
typedef array<int, 3> RangeT;
RangeT rangesArr[maxN];
int res[2][maxN];

int BITree[maxN + 1];
int n = 0;

int Ys[maxN];

int query(int index)
{
    int sum = 0;
    for (; index > 0; index -= -index&index)
    {
        sum += BITree[index];
    }

    return sum;
}

void update(int index, int delta)
{
    for (; index <= n; index += -index&index)
    {
        BITree[index] += delta;
    }
}

void solve() {
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int x = 0, y = 0;
        scanf("%d%d", &x, &y);

        rangesArr[i] = {x, y, i};

        Ys[i] = y;
    }

    sort(Ys, Ys + n);

    int YsSize = unique(Ys, Ys + n) - Ys;

    for (int i = 0; i < n; i++)
    {
        rangesArr[i][1] = lower_bound(Ys, Ys + YsSize, rangesArr[i][1]) - Ys + 1;
    }

    sort(rangesArr, rangesArr + n, [](const RangeT& l, const RangeT& r)
    {
        return l[0] == r[0] ? l[1] > r[1] : l[0] < r[0];
    });

    for (int i = 0; i < n; i++)
    {
        int curY = rangesArr[i][1];

        res[1][rangesArr[i][2]] = i - query(curY - 1);
        update(curY, 1);
    }

    memset(BITree, 0, sizeof(BITree));

    for (int i = n - 1; i >= 0; i--)
    {
        int curY = rangesArr[i][1];
        int innerRanges = query(curY);
        int id = rangesArr[i][2];

        res[0][id] = innerRanges;
        update(curY, 1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", res[0][i]);
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", res[1][i]);
    }
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set<pair<int, int>> orderedSet;

void solve2() {
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int x = 0, y = 0;
        scanf("%d%d", &x, &y);

        rangesArr[i] = {x, y, i};
    }

    sort(rangesArr, rangesArr + n, [](const RangeT& l, const RangeT& r)
    {
        return l[0] == r[0] ? l[1] > r[1] : l[0] < r[0];
    });

    for (int i = 0; i < n; i++)
    {
        int curY = rangesArr[i][1];
        int outRanges = i - orderedSet.order_of_key({curY - 1, INT_MAX});
        int id = rangesArr[i][2];

        res[1][id] = outRanges;
        orderedSet.insert({curY, id});
    }

    orderedSet.clear();

    for (int i = n - 1; i >= 0; i--)
    {
        int curY = rangesArr[i][1];
        int innerRanges = orderedSet.order_of_key({curY, INT_MAX});;
        int id = rangesArr[i][2];

        res[0][id] = innerRanges;
        orderedSet.insert({curY, id});
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", res[0][i]);
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", res[1][i]);
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