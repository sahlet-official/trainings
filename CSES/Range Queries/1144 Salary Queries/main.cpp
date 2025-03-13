#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 2e5;
int salaries[maxN + 1];

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n = 0, q = 0;
    scanf("%d%d", &n, &q);
    
    ordered_set<pair<int, int>> orderedSet;

    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);
        salaries[i] = val;
        orderedSet.insert({val, i});
    }
    
    for (int i = 1; i <= q; i++)
    {
        char ch = 0;
        int a = 0, b = 0;
        scanf(" %c %d %d", &ch, &a, &b);

        if (ch == '!')
        {
            orderedSet.erase({salaries[a], a});
            orderedSet.insert({b, a});

            salaries[a] = b;
        }
        else if (ch == '?')
        {
            int res = orderedSet.order_of_key({b + 1, 0}) - orderedSet.order_of_key({a, 0});

            printf("%d\n", res);
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
        solve();
    }

    return 0;
}