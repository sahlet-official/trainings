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

std::unordered_map<int, std::map<int, int>> primeFactorizationMap(10000);

const std::map<int, int>& primeFactorization(const int n)
{
    {
        auto& res = primeFactorizationMap[n];
        if (!res.empty())
        {
            return res;
        }
    }

    if (n <= 1)
    {
        return primeFactorizationMap[n] = { {1, 1} };
    }

    if (primeNumbersSieve[n])
    {
        return primeFactorizationMap[n] = { {n, 1} };
    }

    for (int primeNumber : primeNumbers)
    {
        int numberOfMults = 0;

        int m = n;

        while (m % primeNumber == 0)
        {
            numberOfMults++;
            m /= primeNumber;
        }

        if (numberOfMults)
        {
            auto& res = primeFactorizationMap[n] = std::map<int, int>(primeFactorization(m));
            res[primeNumber] += numberOfMults;
            return res;
        }
    }

    return primeFactorizationMap[n];
}

const int MOD = 1e9 + 7;

int multMod(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

int multsMod(const std::vector<int>& mults)
{
    int res = 1;
    for (size_t i = 0; i < mults.size(); i++)
    {
        res = multMod(res, mults[i]);
    }

    return res;
}

int multsMod(const std::map<int, int>& mults)
{
    int res = 1;
    for (auto& pair : mults)
    {
        for (int i = 0; i < pair.second; i++)
        {
            res = multMod(res, pair.first);
        }
    }

    return res;
}

// std::vector<int> toFactorMults(int n)
// {
//     if (n <= 0)
//     {
//         n = 1;
//     }

//     std::vector<int> res(n);

//     for (int i = 0; i < n; i++)
//     {
//         res[i] = i + 1;
//     }

//     return res;
// }

std::vector<std::map<int, int>> factorPrimeMultsStorage(100000);

const std::map<int, int>& factorToPrimeMults(int n)
{
    {
        auto& res = factorPrimeMultsStorage[n];

        if (!res.empty())
        {
            return res;
        }
    }

    if (factorPrimeMultsStorage[1].empty())
    {
        factorPrimeMultsStorage[1] = { {1, 1} };
    }

    if (n <= 1)
    {
        return factorPrimeMultsStorage[1];
    }

    int firstEmpty = 2;
    while (!factorPrimeMultsStorage[firstEmpty].empty() && firstEmpty < n)
    {
        firstEmpty++;
    }

    for (int i = firstEmpty; i <= n; i++)
    {
        auto& res = factorPrimeMultsStorage[i] = std::map<int, int>(factorPrimeMultsStorage[i - 1]);
        auto& primeMults = primeFactorization(i);
        for(auto& pair : primeMults)
        {
            if(pair.first != 1)
            {
                factorPrimeMultsStorage[i][pair.first] += pair.second;
            }
        }
    }

    return factorPrimeMultsStorage[n];
}

void divideMults(std::map<int, int>& a, const std::map<int, int>& b)
{
    for(auto& pair : b)
    {
        a[pair.first] -= pair.second;
    }
}

int solve(std::string s) {
    sieveOfEratosthenes();

    std::unordered_map<char, int> counts;
    counts.reserve(300);

    for (char ch : s)
    {
        counts[ch]++;
    }

    auto mainFactorMults = factorToPrimeMults(s.size() / 2);

    for (auto& pair : counts)
    {
        auto& divisionFactorMults = factorToPrimeMults(pair.second / 2);

        divideMults(mainFactorMults, divisionFactorMults);
    }

    int res = multsMod(mainFactorMults);

    return res;
}

#include <fstream>

int main()
{
    //std::ios::sync_with_stdio(false);

    std::ifstream f("input.txt");
    
    std::string s;
    getline(f, s);
    f.close();

    int result = solve(s);

    std::cout << result << "\n";
    

    return 0;
}