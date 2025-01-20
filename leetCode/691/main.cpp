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
const int primeNumbersSize = 100;
std::vector<int> primeNumbers;
std::unordered_map<int, int> primeNumbersIds(primeNumbersSieveSize);

void sieveOfEratosthenes()
{
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

    inline std::vector<char> subtract(std::vector<char>& targetLetters, const std::vector<char>& sticker, int& subtractedCount, bool edit = false)
    {
        std::vector<char> res(targetLetters.size(), 0);
        for (int i = 0; i < targetLetters.size(); i++)
        {
            int value = min(targetLetters[i], sticker[i]);
            subtractedCount += value;
            res[i] = value;
            if (edit)
            {
                targetLetters[i] -= value;
            }
        }

        return std::move(res);
    }

    int minRes = 0;
    std::vector<std::vector<char>> stickersLetters;
    std::vector<char> targetLetters;

    inline std::vector<char> intersection(int stickersLettersIndex)
    {
        std::vector<char> res(targetLetters.size(), 0);

        for (size_t i = 0; i < targetLetters.size(); i++)
        {
            res[i] = min(targetLetters[i], stickersLetters[stickersLettersIndex][i]);
        }
        
        return res;
    }

    long long getNextFilter(long long prevFilter)
    {
        //long long nextFilter = prevFilter;
        long long worse = 0;
        long long checked = 0;

        for (int i = 0; i < (int)stickersLetters.size() - 1; i++)
        {
            long long id1 = 1ll << i;
            if (prevFilter & id1 || worse & id1 || checked & id1)
            {
                continue;
            }

            auto intersection1 = intersection(i);

            for (int j = i + 1; j < stickersLetters.size(); j++)
            {
                long long id2 = 1ll << j;
                if (prevFilter & id2 || worse & id2)
                {
                    continue;
                }

                auto intersection2 = intersection(j);

                bool worse1 = false;
                bool worse2 = false;

                for (size_t i = 0; i < intersection2.size() && (!worse1 || !worse2); i++)
                {
                    if (intersection1[i] < intersection2[i])
                    {
                        worse1 = true;
                    }

                    if (intersection1[i] > intersection2[i])
                    {
                        worse2 = true;
                    }
                }
                
                if (!worse1 || !worse2)
                {
                    if (worse1)
                    {
                        worse = worse | id1;
                        intersection1 = intersection2;
                        id1 = id2;
                        checked = checked | id2;
                    }
                    else
                    {
                        worse = worse | id2;
                    }
                }
            }
        }

        return prevFilter | worse;
    }

    void recursion(int prevUsed, int stickerIndex, long long filter)
    {
        if (prevUsed + 1 >= minRes)
        {
            return;
        }

        if (stickerIndex >= stickersLetters.size())
        {
            return;
        }

        long long nextFilter = 0; //getNextFilter(filter);
        // if (nextFilter & (1ll << stickerIndex))
        // {
        //     recursion(prevUsed, stickerIndex + 1, filter);
        //     return;
        // }

        int used = 0;
        for (size_t i = 0; i < stickersLetters[stickerIndex].size(); i++)
        {
            if (targetLetters[i] > 0 && stickersLetters[stickerIndex][i] > 0)
            {
                used = max(used, ((targetLetters[i] - 1) / stickersLetters[stickerIndex][i]) + 1);
            }
        }

        for (size_t i = 0; i < targetLetters.size(); i++)
        {
            targetLetters[i] -= used * stickersLetters[stickerIndex][i];
        }
        

        bool lettersLeft = false;
        for (size_t i = 0; i < targetLetters.size(); i++)
        {
            if (targetLetters[i] > 0)
            {
                lettersLeft = true;
                break;
            }
        }
        
        if (!lettersLeft)
        {
            if (prevUsed + used < minRes)
            {
                minRes = prevUsed + used;

                for (int i = 0; i < 2 && used; i++)
                {
                    for (size_t i = 0; i < targetLetters.size(); i++)
                    {
                        targetLetters[i] += stickersLetters[stickerIndex][i];
                    }
                    used--;
                }
            }
        }

        while (used)
        {
            if (prevUsed + used + 1 < minRes)
            {
                recursion(prevUsed + used, stickerIndex + 1, nextFilter);
            }

            for (size_t i = 0; i < targetLetters.size(); i++)
            {
                targetLetters[i] += stickersLetters[stickerIndex][i];
            }

            used--;
        }

        recursion(prevUsed, stickerIndex + 1, nextFilter);
    }

public:
    int minStickers(vector<string>& stickers, string target) {
        //count greedy

        std::vector<char> targetLettersNative(26, 0);
        
        // fill
        int targetLettersLength = 0;
        std::vector<char> targetLettersIndices(26, -1);
        int targetLettersCount = 0;
        int targetLettersCountCopy = 0;
        for (int i = 0; i < target.size(); i++) {
            targetLettersNative[target[i] - 'a']++;
            if (targetLettersNative[target[i] - 'a'] == 1)
            {
                targetLettersIndices[target[i] - 'a'] = targetLettersLength;
                targetLettersLength++;
            }
            targetLettersCount++;
        }
        targetLettersCountCopy = targetLettersCount;

        targetLetters = std::vector<char>(targetLettersLength, 0);
        stickersLetters = std::vector<std::vector<char>>(stickers.size(), std::vector<char>(targetLettersLength, 0));

        for (int i = 0; i < targetLettersIndices.size(); i++) {
            if (targetLettersIndices[i] >= 0)
            {
                targetLetters[targetLettersIndices[i]] = targetLettersNative[i];
            }
        }

        std::vector<bool> existingLetters(targetLettersLength, false);

        for (int j = 0; j < stickers.size(); j++) {
            for (int i = 0; i < stickers[j].size(); i++) {
                if (targetLettersIndices[stickers[j][i] - 'a'] >= 0)
                {
                    stickersLetters[j][targetLettersIndices[stickers[j][i] - 'a']]++;
                    existingLetters[targetLettersIndices[stickers[j][i] - 'a']] = true;
                }
            }
        }

        // check possibility
        for (int i = 0; i < existingLetters.size(); i++) {
            if (!existingLetters[i])
            {
                return -1;
            }
        }

        long long filter = getNextFilter(0);

        {
            auto stickersLettersMove = std::move(stickersLetters);
            int stickersLettersSize = stickersLettersMove.size();
            for (int i = 0; i < stickersLettersMove.size(); i++)
            {
                if (filter & (1ll << i))
                {
                    stickersLettersSize--;
                }
            }

            stickersLetters.resize(stickersLettersSize);
            int stickersLettersIndex = 0;

            for (int i = 0; i < stickersLettersMove.size(); i++)
            {
                if (!(filter & (1ll << i)))
                {
                    stickersLetters[stickersLettersIndex] = std::move(stickersLettersMove[i]);
                    stickersLettersIndex++;
                }
            }
        }


        // while targetLetters > 0 - find the best from stickersLetters, subtract
        std::vector<bool> dropout(stickersLetters.size(), false);
        std::vector<char> targetLettersCopy = targetLetters;
        int greedyRes = 0;
        while(targetLettersCount)
        {
            int maxSubtractingLetters = 0;
            int maxSubtractingLettersIndex = -1;

            for (int i = 0; i < stickersLetters.size(); i++) {
                if (dropout[i])
                {
                    continue;
                }

                int subtractingLetters = 0;
                subtract(targetLettersCopy, stickersLetters[i], subtractingLetters, false);

                if (maxSubtractingLetters < subtractingLetters)
                {
                    maxSubtractingLetters = subtractingLetters;
                    maxSubtractingLettersIndex = i;
                }

                if (subtractingLetters == 0)
                {
                    dropout[i] = true;
                }
            }

            targetLettersCount -= maxSubtractingLetters;
            subtract(targetLettersCopy, stickersLetters[maxSubtractingLettersIndex], maxSubtractingLetters, true);
            greedyRes++;
        }

        this->minRes = greedyRes;

        recursion(0, 0, 0);

        return minRes;
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
    vector<string> v;

    v = {"indicate","why","finger","star","unit","board","sister","danger","deal","bit","phrase","caught","if","other","water","huge","general","read","gold","shall","master","men","lay","party","grow","view","if","pull","together","head","thank","street","natural","pull","raise","cost","spoke","race","new","race","liquid","me","please","clear","could","reply","often","huge","old","nor"};
    out << (s.minStickers(v, "fhhfiyfdcwbycma") == 9) << std::endl;
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