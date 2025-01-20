#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    int const MOD = 1e9 + 7;

    long long modMult(long long a, long long b)
    {
        return ((a  % MOD) * (b  % MOD)) % MOD;
    }

    long long modSum(long long a, long long b)
    {
        return ((a  % MOD) + (b  % MOD) + MOD) % MOD;
    }

    long long modPow(long long a, long long n)
    {
        long long res = 1;
        while (n)
        {
            if (n % 2)
            {
                res = modMult(res, a);
                n--;
            }

            n /= 2;
            a = modMult(a, a);
        }
        
        return res;
    }

    std::vector<int> factors = std::vector<int> (101);

    int factorMod(int n)
    {
        if (n <= 1)
        {
            return 1;
        }

        if (factors[n])
        {
            return factors[n];
        }

        int res = modMult(n, factorMod(n - 1));

        factors[n] = res;

        return res;
    }

    int factorPartMod(int n, int k)
    {
        int res = 1;
        for (int i = 0; i < k; i++)
        {
            res = modMult(res, n - i);
        }

        return res;
    }

    long long modInverse(long long a) {
        return modPow(a, MOD - 2);
    }

    int combinations(int n, int m)
    {
        int res =  modMult(factorMod(n), modInverse(modMult(factorMod(m), factorMod(n - m))));

        return res;
    }

    int solutionWithGaps(int n, int goal, int k)
    {
        int res = factorPartMod(n, k);

        int n_subtr_k_pow = modPow(n - k, goal - k);

        res = modMult(res, n_subtr_k_pow);

        return res;
    }

    int solution(int n, int goal, int k)
    {
        int res = solutionWithGaps(n, goal, k);

        int sign = -1;

        for(int i = 1; i < n - k; i++)
        {
            res =  modSum(
                res,
                sign * modMult(
                    solutionWithGaps(n - i, goal, k),
                    combinations(n, i)
                )
            );

            sign *= -1;
        }

        return res;
    }

    int numMusicPlaylists(int n, int goal, int k) {
        int res = solution(n, goal, k);

        return res;
    }
};


void solve(std::istream& in, std::ostream& out)
{

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