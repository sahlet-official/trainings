#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxN = 2 * 1e5;
ordered_set<int> orderedSet;
 
void solve() {
    int n = 0, k = 0;
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
    {
        orderedSet.insert(i);
    }

    int index = 0;

    while (!orderedSet.empty())
    {
        index += k;
        index %= orderedSet.size();
        int x = *orderedSet.find_by_order(index);
        orderedSet.erase(x);
        
        printf("%d ", x);
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