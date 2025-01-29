#include <iostream>
#include <bits/stdc++.h>

using namespace std;

std::deque<pair<char, char>> res;

inline void formBHG(char B, char H, char G, char* BHG)
{
    BHG[B-1] = 'B';
    BHG[H-1] = 'H';
    BHG[G-1] = 'G';
}

void solve(char from, int to, int n) {
    if (n == 1)
    {
        cout << (int)from << " " << (int)to << endl;
        return;
    }

    char other = 6 - (from + to);
    solve(from, other, n - 1);
    solve(from, to, 1);
    solve(other, to, n - 1);
}
 
void solve() {
    int n = 0;
    cin >> n;

    res.clear();

    cout << ((1 << n) - 1) << endl;

    solve(1, 3, n);
    
}


int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}