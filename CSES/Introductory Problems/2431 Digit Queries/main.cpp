#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    long long k = 0;
    cin >> k;

    long long left = 0;

    int dimension = 0;

    long long upper = 1;

    while (left < k)
    {
        dimension++;
        upper *= 10;

        left += dimension * upper/10 * 9;
    }

    left -= dimension * upper/10 * 9;

    k = k - left;

    long long number = k / dimension + (k % dimension ? 1 : 0) + (upper / 10 - 1);

    int digit = dimension - (k % dimension ? k % dimension : dimension) + 1;

    long long divider = 1;

    for (int i = 1; i <= digit; i++)
    {
        divider *= 10;
    }

    int res = (number % divider) / (divider / 10);
    
    cout << res << endl;
}

long long pow10(int p)
{
    long long res = 1;
    for (int i = 0; i < p; i++)
    {
        res *= 10;
    }
    
    return res;
}

void solve2() {
    long long k = 0;
    cin >> k;

    k--;

    long long left = 0;

    int dimension = 1;

    {
        long long val = 0;
        while (val = 9 * pow10(dimension - 1) * dimension, val < k)
        {
            k -= val;
            dimension++;
        }
    }

    long long number = k / dimension + pow10(dimension - 1);

    cout << (to_string(number)[k % dimension] - '0') << endl;
}


int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve2();
    }

    return 0;
}