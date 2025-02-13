#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n = 0;
    scanf("%d", &n);

    int res = 0;

    while (n > 0)
    {
        int minV = n;

        int num = n;

        while (num)
        {
            int digit = num % 10;
            num /= 10;
            
            int subres = n - digit;

            minV = min(minV, subres);
        }

        n = minV;

        res++;
    }
    

    printf("%d", res);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}