#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;

long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}


// std::vector<long long> resStorage(501, 0);
std::vector<long long> factors(51);

class Solution {
public:
    
    int factor(int n)
    {
        if (n == 1 || n == 0)
        {
            return 1;
        }

        if (factors[n])
        {
            return factors[n];
        }

        factors[n] = n * factor(n - 1);

        return factors[n];
    }

    double getCombinations(vector<int>& balls, int k1, int k2, int step, int left, int half)
    {
        if (step > balls.size() || k1 > balls.size() || k2 > balls.size())
        {
            return 0;
        }

        if (step == balls.size())
        {
            if (left == half)
            {
                if (k1 == k2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else if (step < balls.size())
        {
            if (left == half)
            {
                k2 += balls.size() - step;

                if (k1 == k2)
                {
                    double res = 1;
                    for (int i = step; i < balls.size(); i++)
                    {
                        res /= factor(balls[i]);
                    }

                    return res;
                }
                else
                {
                    return 0;
                }
            }
        }

        double res = 0;

        res += getCombinations(balls, k1, k2 + 1, step + 1, left, half) / factor(balls[step]);

        for (int i = 1; i <= balls[step] - 1; i++)
        {
            res += getCombinations(balls, k1 + 1, k2 + 1, step + 1, left - i, half) / factor(i) / factor(balls[step] - i);
        }

        res += getCombinations(balls, k1 + 1, k2, step + 1, left - balls[step], half) / factor(balls[step]);

        return res;
    }

    double getCombinations(vector<int>& balls)
    {
        int n = 0;

        for (size_t i = 0; i < balls.size(); i++)
        {
            n += balls[i];
        }

        int half = n/2;

        double res = getCombinations(balls, 0, 0, 0, n, half);
        
        return res;
    }

    double getProbabilityOfOneCombination(vector<int>& balls)
    {
        int n = 0;

        for (size_t i = 0; i < balls.size(); i++)
        {
            n += balls[i];
        }

        double res = 1;

        int half = n/2;
        for (size_t i = 1; i <= half; i++)
        {
            res *= (double) i / (double) (half + i);
        }

        //res *= factor(n);

        for (size_t i = 0; i < balls.size(); i++)
        {
            res *= factor(balls[i]);
        }

        return res;
    }

    double getProbability(vector<int>& balls) {
        double p1 = getProbabilityOfOneCombination(balls);
        double n = getCombinations(balls);

        return p1 * n;
        // return n;
        //return p1;
    }
};


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<int> v;

    v = {1, 1};
    out << s.getProbability(v) - 1.0 << std::endl;
    v = {2, 1, 1};
    out << s.getProbability(v) - 0.66667 << std::endl;
    v = {1, 2, 1, 2};
    out << s.getProbability(v) - 0.6 << std::endl;
    v = {3, 2, 1};
    out << s.getProbability(v) - 0.3 << std::endl;

    // v = {1, 1};
    // out << s.getProbability(v) << std::endl;
    // v = {2, 1, 1};
    // out << s.getProbability(v) << std::endl;
    // v = {1, 2, 1, 2};
    // out << s.getProbability(v) << std::endl;
    // v = {3, 2, 1};
    // out << s.getProbability(v) << std::endl;
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