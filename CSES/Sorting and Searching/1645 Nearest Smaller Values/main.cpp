#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
pair<int, int> nearest[maxN + 1]; // similar to LIS
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    nearest[0] = {0, 0};

    int size = 1;

    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        int closest = 0;

        
        if (val <= nearest[size - 1].first)
        {
            size = lower_bound(nearest + 0, nearest + size, make_pair(val, 0),
                [](const pair<int, int>& l, const pair<int, int>& r) -> bool {
                    return l.first < r.first;
                }
            ) - nearest;
        }

        nearest[size] = { val, i };
        closest = nearest[size - 1].second;
        size++;

        printf("%d ", closest);
    }
}

void solve2() {
    int n = 0;
    scanf("%d", &n);

    stack<pair<int, int>> s;
    s.emplace(0, 0);

    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        while (s.top().first >= val)
        {
            s.pop();
        }

        printf("%d ", s.top().second);

        s.emplace(val, i);
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
        solve2();
    }
 
    return 0;
}