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
    a %= MOD;
    b %= MOD;
    if (a % b == 0) {
        return a / b;
    }

    return modMult(a, modInverse(b));
}

const int primeNumbersSieveSize = 500;
bool primeNumbersSieve[primeNumbersSieveSize];
std::deque<int> primeNumbers;
std::unordered_map<int, int> primeNumbersIds(primeNumbersSieveSize);

void sieveOfEratosthenes()
{
    primeNumbers.clear();

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

std::unordered_map<int, std::vector<int>> primeFactorizationMap(1000);

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

std::list<std::pair<int /*number*/, int /*power*/>> primeFactorizationWithoutStorage(int n)
{
    auto res = std::list<std::pair<int /*number*/, int /*power*/>>();

    if (n <= 1)
    {
        return res;
    }

    if (primeNumbersSieve[n])
    {
        res.emplace_back(n, 1);
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
            res.emplace_back(primeNumber, numberOfMults);
        }
    }

    if (n > 1)
    {
        res.emplace_back(n, 1);
    }

    return res;
}

class Union
{
    std::vector<int> parents;

public:
    Union(int n) : parents(n)
    {
        iota(parents.begin(), parents.end(), 0);
    }

    int find(int node)
    {
        return parents[node] == node ? parents[node] : (parents[node] = find(parents[node]));
    }

    bool connected(int n1, int n2)
    {
        return find(n1) == find(n2);
    }

    bool connect(int n1, int n2)
    {
        int parent1 = find(n1);
        int parent2 = find(n2);

        if(parent1 == parent2)
        {
            return false;
        }

        parents[parent1] = parent2;

        return true;
    }
};

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int N = nums.size();

        vector<int> lisLength(N, 1);
        vector<int> ldsLength(N, 1);

        // Stores the length of longest increasing subsequence that ends at i.
        for (int i = 0; i < N; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] > nums[j]) {
                    lisLength[i] = max(lisLength[i], lisLength[j] + 1);
                }
            }
        }

        // Stores the length of longest decreasing subsequence that starts at i.
        for (int i = N - 1; i >= 0; i--) {
            for (int j = i + 1; j < N; j++) {
                if (nums[i] > nums[j]) {
                    ldsLength[i] = max(ldsLength[i], ldsLength[j] + 1);
                }
            }
        }

        int minRemovals = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (lisLength[i] > 1 && ldsLength[i] > 1) {
                minRemovals =
                    min(minRemovals, N - lisLength[i] - ldsLength[i] + 1);
            }
        }

        return minRemovals;
    }
};

class Solution2 {
public:
    vector<int> getLongestIncreasingSubsequenceLength(vector<int>& v) {
        vector<int> lisLen(v.size(), 1);
        vector<int> lis = {v[0]};

        for (int i = 1; i < v.size(); i++) {
            // Index of the first element which is equal to or greater than
            // v[i].
            int index = lower_bound(lis.begin(), lis.end(), v[i]) - lis.begin();

            // Add to the list if v[i] is greater than the last element.
            if (index == lis.size()) {
                lis.push_back(v[i]);
            } else {
                // Assign the value v[i] to the returned index as it's going to
                // smaller than or equal to the existing element.
                lis[index] = v[i];
            }

            lisLen[i] = index + 1;
        }

        return lisLen;
    }

    int minimumMountainRemovals(vector<int>& nums) {
        int N = nums.size();
        vector<int> lisLength = getLongestIncreasingSubsequenceLength(nums);

        reverse(nums.begin(), nums.end());
        vector<int> ldsLength = getLongestIncreasingSubsequenceLength(nums);
        // Reverse the length array to correctly depict the lenght of longest
        // decreasing subsequence for each index.
        reverse(ldsLength.begin(), ldsLength.end());

        int minRemovals = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (lisLength[i] > 1 && ldsLength[i] > 1) {
                minRemovals =
                    min(minRemovals, N - lisLength[i] - ldsLength[i] + 1);
            }
        }

        return minRemovals;
    }
};


bool equal(int i1, int i2)
{
    return i1 == i2;
}

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

bool equal(const vector<double>& v1, const vector<double>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (v1[i] - v2[i] > 0.000006)
        {
            return false;
        }
    }
    
    return true;
}

bool equal(double a, double b)
{
    if (a - b > 0.000006)
    {
        return false;
    }
    
    return true;
}

template<typename T>
bool equal(const vector<T>& v1, const vector<T>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (!equal(v1[i], v2[i]))
        {
            return false;
        }
    }
    
    return true;
}


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    Solution2 s2;
    vector<int> v;

    v = {2, 3, 1};
    s.minimumMountainRemovals(v);
    s2.minimumMountainRemovals(v);
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