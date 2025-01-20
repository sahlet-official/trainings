#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;

inline long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

inline long long modPow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if (b % 2)
        {
            res = modMult(res, a);
        }

        b /= 2;
        a = modMult(a, a);
    }

    return res;
}

inline long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

inline long long modDivide(long long a, long long b)
{
    return modMult(a, modInverse(b));
}

const int factorialStorageSize = 100001;
int factorial[factorialStorageSize] = {1};
int invFactorial[factorialStorageSize] = {1};
void countFactorials() {
    if (factorial[1]) {
        return;
    }

    for (int i = 1; i < factorialStorageSize; i++) {
        factorial[i] = modMult(i, factorial[i - 1]);
        invFactorial[i] = modInverse(factorial[i]);
    }
}

// int factorial[1001] = {1};
// int invFactorial[1001] = {1};

int fStorage[1001][1001] = {};

class Solution {
    // void countFactorials() {
    //     if (factorial[1]) {
    //         return;
    //     }

    //     for (int i = 1; i <= 1000; i++) {
    //         factorial[i] = modMult(i, factorial[i - 1]);
    //         invFactorial[i] = modInverse(factorial[i]);
    //     }
    // }

    void fillFStorage() {
        if (fStorage[1][1])
        {
            return;
        }

        fStorage[1][1] = 1;
        for (int i = 2; i <= 1000; i++)
        {
            fStorage[i][1] = modMult(fStorage[i - 1][1], i - 1);
            fStorage[i][i] = 1;
        }

        for (int n = 2; n <= 1000; n++)
        {
            for (int k = 2; k < n; k++)
            {
                fStorage[n][k] = modSum(fStorage[n - 1][k - 1], modMult(fStorage[n - 1][k], n - 1));
            }
        }
        
    }

public:
    int rearrangeSticks(int n, int k) {
        //countFactorials();
        fillFStorage();

        return fStorage[n][k];
    }
};


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<int> v;

    //v = {2, 3};
    out << (s.rearrangeSticks(3, 2) == 3) << std::endl;
    out << (s.rearrangeSticks(5, 5) == 1) << std::endl;
    out << (s.rearrangeSticks(20, 11) == 647427950) << std::endl;
    //out << (s.rearrangeSticks(3, 2) == 3) << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    //std::cout << "hello dude";

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    // solve(std::cin, std::cout);
    // solve(std::cin, fout);
    solve(fin, std::cout);
    // solve(fin, fout);
    

    return 0;
}