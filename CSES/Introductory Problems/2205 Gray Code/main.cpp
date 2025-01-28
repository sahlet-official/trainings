#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void print(const std::vector<bool>& str)
{
    for (int i = 1; i < str.size(); i++)
    {
        cout << (str[i] ? 1 : 0);
    }
    
    cout << endl;
}
 
void solve() {
    int n = 0;
    cin >> n;

    std::vector<bool> str(n + 1, false);
    print(str);

    for(int i = 1; i < (1 << n); i++)
    {
        int firstTrueBit = __builtin_ffs(i);
        str[firstTrueBit] = str[firstTrueBit] ^ true;
        print(str);
    }
}

void print(int mask, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << ((mask & (1 << i)) ? 1 : 0);
    }
    
    cout << endl;
}

void solve2() {
    int n = 0;
    cin >> n;

    std::vector<bool> memory(1 << n, false);

    int mask = 0;
    print(mask, n);
    memory[mask] = true;

    for(int i = 0; i < n;)
    {
        int newMask = mask ^ (1 << i);
        if (!memory[newMask])
        {
            memory[newMask] = true;
            mask = newMask;
            print(mask, n);
            i = 0;
            continue;
        }

        i++;
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