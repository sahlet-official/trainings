#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxN = 2 * 1e5;
int arr[maxN];
int res[maxN];
int N, K;
 
void solve() {
    scanf("%d%d", &N, &K);
 
    for (int i = 0; i < N; i++)
    {
        int val = 0;
        scanf("%d", &val);

        arr[i] = val;
    }

    ordered_set<pair<int, int>> orderedSet;

    for (int i = 0; i < K - 1; i++)
    {
        orderedSet.insert({arr[i], i});
    }

    int medianIndex = ((K + 1) / 2) - 1;

    for (int l = 0, r = K - 1; r < N; l++, r++)
    {
        orderedSet.insert({arr[r], r});

        int median = orderedSet.find_by_order(medianIndex)->first;

        res[l] = median;

        orderedSet.erase({arr[l], l});
    }

    for (size_t i = 0; i < N - K + 1; i++)
    {
        printf("%d ", res[i]);
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