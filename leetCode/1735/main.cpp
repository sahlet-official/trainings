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

long long modPow(long long a, long long b)
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

long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

long long modDivide(long long a, long long b)
{
    return modMult(a, modInverse(b));
}

const int primeNumbersSieveSize = 10001;
bool primeNumbersSieve[primeNumbersSieveSize];
const int primeNumbersSize = 2000;
std::vector<int> primeNumbers;
//std::unordered_map<int, int> primeNumbersIds(primeNumbersSieveSize);

void sieveOfEratosthenes()
{
    if (primeNumbers.size()) {
        return;
    }

    primeNumbers.clear();
    primeNumbers.reserve(primeNumbersSize);

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
        
            //primeNumbersIds[i] = primeNumbers.size() - 1;
        }
    }
}

std::vector<int> createPrimeMultStorageVect()
{
    std::vector<int> res(primeNumbers.size());

    return res;
}

void addVecTo(std::vector<int>& a, const std::vector<int>& b)
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i] += b[i];
    }
}

void subtractVecFrom(std::vector<int>& a, const std::vector<int>& b)
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i] -= b[i];
    }
}

int collapseVec(const std::vector<int>& a)
{
    int res = 1;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i]; j++)
        {
            res *= primeNumbers[i];
        }
    }

    return res;
}

// std::unordered_map<int, std::vector<int>> primeFactorizationMap(1000);

/* const std::vector<int>& primeFactorization(const int n)
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
} */

std::list<int> primeFactorizationWithoutStorage(int n)
{
    auto res = std::list<int>();

    if (n <= 1)
    {
        return res;
    }

    if (primeNumbersSieve[n])
    {
        res.push_back(1);
        return res;
    }

    for (int primeNumber : primeNumbers)
    {
        if (primeNumber * primeNumber > n)
        {
            break;
        }

        int numberOfMults = 0;

        while (n % primeNumber == 0)
        {
            numberOfMults++;
            n /= primeNumber;
        }

        if (numberOfMults)
        {
            res.push_back(numberOfMults);
        }
    }

    if (n > 1)
    {
        res.push_back(1);
    }

    return res;
}



class Solution {
    std::vector<std::vector<int>> storage;
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        sieveOfEratosthenes();

        if (!storage.size())
        {
            const int width = 10001;
            const int height = 16;

            storage.resize(height);
            for (int i = 0; i < storage.size(); i++)
            {
                storage[i].resize(width);
            }

            for (size_t j = 1; j < width; j++)
            {
                storage[1][j] = j;
            }

            for (size_t i = 1; i < height; i++)
            {
                storage[i][1] = 1;
            }

            for (size_t i = 2; i < height; i++)
            {
                for (size_t j = 1; j < width; j++)
                {
                    storage[i][j] = modSum(storage[i - 1][j], storage[i][j - 1]);
                }
            }
        }

        vector<int> respond;
        respond.reserve(queries.size());

        for(auto query : queries)
        {
            int n = query[0];
            int k = query[1];

            int res = 1;

            auto factorsCounts = primeFactorizationWithoutStorage(k);

            for (int factorCount : factorsCounts)
            {
                // if (!factorCount)
                // {
                //     continue;
                // }

                int combinations = storage[factorCount][n];
                res = modMult(combinations, res);
            }

            respond.push_back(res);
        }

        return respond;
    }
};

bool equal(const vector<int>& v1, const vector<int>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }
    
    return true;
}

void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<vector<int>> v;

    v = {{2,6},{5,1},{73,660}};
    out << equal(s.waysToFillArray(v), {4,1,50734910}) << std::endl;
    v = {{1,1},{2,2},{3,3},{4,4},{5,5}};
    out << equal(s.waysToFillArray(v), {1,2,3,10,5}) << std::endl;
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