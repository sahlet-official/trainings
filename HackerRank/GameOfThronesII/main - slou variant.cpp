#include <iostream>
#include <bits/stdc++.h>

const int primeNumbersSieveSize = 1e7;
bool primeNumbersSieve[primeNumbersSieveSize];
std::list<int> primeNumbers;

void sieveOfEratosthenes()
{
    for (size_t i = 0; i < primeNumbersSieveSize; i++)
    {
        primeNumbersSieve[i] = true;
    }

    primeNumbersSieve[0] = false;
    primeNumbersSieve[1] = false;

    for (size_t i = 2; i * i < primeNumbersSieveSize; i++)
    {
        if (!primeNumbersSieve[i])
        {
            continue;
        }

        primeNumbers.push_back(i);

        for (size_t j = i * i; j < primeNumbersSieveSize; j += i)
        {
            primeNumbersSieve[j] = false;
        }
    }
}

std::unordered_map<int, std::list<int>> primeFactorizationMap(10000);

const std::list<int>& primeFactorization(int n)
{
    std::list<int>& res = primeFactorizationMap[n];
    if (res.size())
    {
        return res;
    }

    for (int primeNumber : primeNumbers)
    {
        while (n % primeNumber == 0)
        {
            res.push_back(primeNumber);
            n /= primeNumber;
        }

        if (n < primeNumber)
        {
            break;
        }
    }

    return res;
}

const int MOD = 1e9 + 7;

int multMod(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

int multsMod(std::vector<int> mults)
{
    int res = 1;
    for (size_t i = 0; i < mults.size(); i++)
    {
        res = multMod(res, mults[i]);
    }

    return res;
}

std::vector<int> toFactorMults(int n)
{
    if (n <= 0)
    {
        n = 1;
    }

    std::vector<int> res(n);

    for (int i = 0; i < n; i++)
    {
        res[i] = i + 1;
    }

    return res;
}

std::vector<int> divideMults(std::vector<int> a, const std::vector<int>& b)
{
    for(int mult : b)
    {
        auto primes = primeFactorization(mult);

        for(int divisor : primes)
        {
            for (int i = a.size() - 1; i >= 0; i--)
            {
                if (a[i] >= 1 && a[i] % divisor == 0)
                {
                    a[i] /= divisor;
                    break;
                }
            }
        }
    }

    return a;
}

int solve(std::string s) {
    sieveOfEratosthenes();

    std::unordered_map<char, int> counts;
    counts.reserve(300);

    for (char ch : s)
    {
        counts[ch]++;
    }

    auto mainFactorMults = toFactorMults(s.size() / 2);

    for (auto& pair : counts)
    {
        auto divisionFactorMults = toFactorMults(pair.second / 2);

        mainFactorMults = divideMults(mainFactorMults, divisionFactorMults);
    }

    int res = multsMod(mainFactorMults);

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    std::string s;
    getline(std::cin, s);

    int result = solve(s);

    std::cout << result << "\n";
    

    return 0;
}