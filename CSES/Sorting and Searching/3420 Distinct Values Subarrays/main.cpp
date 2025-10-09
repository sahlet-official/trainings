#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int N, L = 1, R;
unordered_map<int /*val*/ , int /*index*/> lastEntry;
 
void solve() {
    scanf("%d", &N);

    lastEntry.reserve(3*N);

    long long res = 0;
 
    for (int i = 0; i < N; i++) {
        int val = 0;
        scanf("%d", &val);

        R++;

        auto iter = lastEntry.find(val);

        if (iter != lastEntry.end()) {
            if (iter->second >= L) {
                L = iter->second + 1;
            }
        }

        lastEntry[val] = R;

        res += R - L + 1;
    }

    printf("%lld", res);
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