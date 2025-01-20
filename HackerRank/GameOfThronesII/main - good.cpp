#include <iostream>
#include <bits/stdc++.h>

const int primeNumbersSieveSize = 50000;
bool primeNumbersSieve[primeNumbersSieveSize];
std::vector<int> primeNumbers;
std::unordered_map<int, int> primeNumbersIds(primeNumbersSieveSize);

void sieveOfEratosthenes()
{
    primeNumbers.clear();
    primeNumbers.reserve(10000);

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

        for (size_t j = i * i; j < primeNumbersSieveSize; j += i)
        {
            primeNumbersSieve[j] = false;
        }
    }

    for (int i = 0; i < primeNumbersSieveSize; i++)
    {
        if (primeNumbersSieve[i])
        {
            primeNumbers.push_back(i);
        
            primeNumbersIds[i] = primeNumbers.size() - 1;
        }
    }
}

std::vector<int> createPrimeMultStorageVect()
{
    std::vector<int> res(primeNumbers.size());

    return res;
}

std::unordered_map<int, std::vector<int>> primeFactorizationMap(10000);

const std::vector<int>& primeFactorization(const int n)
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
        auto& res = primeFactorizationMap[n] = createPrimeMultStorageVect();
        return res;
    }

    if (primeNumbersSieve[n])
    {
        auto& res = primeFactorizationMap[n] = createPrimeMultStorageVect();
        res[primeNumbersIds[n]] = 1;
        return res;
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
            auto& res = primeFactorizationMap[n] = std::vector<int>(primeFactorization(m));
            res[primeNumbersIds[primeNumber]] += numberOfMults;
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
    for (int i = 0; i < mults.size(); i++)
    {
        for (int j = 0; j < mults[i]; j++)
        {
            res = multMod(res, primeNumbers[i]);
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

std::vector<std::vector<int>> factorPrimeMultsStorage(100000);

const std::vector<int>& factorToPrimeMults(int n)
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
        auto& res = factorPrimeMultsStorage[1] = createPrimeMultStorageVect();
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
        auto& res = factorPrimeMultsStorage[i] = std::vector<int>(factorPrimeMultsStorage[i - 1]);

        auto& primeMults = primeFactorization(i);

        for(int j = 0; j < primeMults.size(); j++)
        {
            res[j] += primeMults[j];
        }
    }

    return factorPrimeMultsStorage[n];
}

void divideMults(std::vector<int>& a, const std::vector<int>& b)
{
    for(int i = 0; i < a.size(); i++)
    {
        a[i] -= b[i];
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