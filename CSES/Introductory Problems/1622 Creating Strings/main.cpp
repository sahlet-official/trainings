#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    string s;
    cin >> s;

    sort(s.begin(), s.end());

    int count = 1;

    for (size_t i = 2; i <= s.size(); i++)
    {
        count *= i;
    }

    int divider = 1;

    for (size_t i = 1; i < s.size(); i++)
    {
        if (s[i] == s[i-1])
        {
            divider++;
            count /= divider;
        }
        else
        {
            divider = 1;
        }
    }

    cout << count << endl;

    cout << s << endl;

    while (next_permutation(s.begin(), s.end()))
    {
        cout << s << endl;
    }
    
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