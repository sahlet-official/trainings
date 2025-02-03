#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0;
    cin >> n;

    unordered_set<int> set;
    set.reserve(4*100000);

    for (int i = 0; i < n; i++)
    {
        int number = 0;
        cin >> number;
        
        set.insert(number);
    }
    
    cout << set.size() << endl;
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