#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0, q = 0;
    cin >> n >> q;

    long long sum = 0;

    std::vector<long long> staticSum(n);

    for (int i = 0; i < n; i++)
    {
        int elem = 0;
        cin >> elem;
        sum += elem;

        staticSum[i] = sum;
    }
    
    for (int i = 0; i < q; i++)
    {
        int a = 0, b = 0;
        cin >> a >> b;

        a--;
        b--;

        cout << (staticSum[b] - (a ? staticSum[a - 1] : 0)) << endl;
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