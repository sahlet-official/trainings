#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long maxA = 1e18;

long long a = 0, b = 0;

long long solver(const string& s, int pos = 0)
{
    if (pos == 0)
    {
        long long res = 0;

        for (size_t i = 1; i < s.length(); i++)
        {
            long long subRes = 1;

            for (size_t j = i; j < s.length(); j++)
            {
                subRes *= 9;
            }

            res += subRes;
        }

        return res + solver("0" + s, 1) + 1;
    }

    int curDigit = s[pos] - '0';
    int prevDigit = s[pos - 1] - '0';

    long long res = (curDigit - 1) + (prevDigit >= curDigit ? 0 : -1) + 1;

    if (res > 0)
    {
        for (int i = pos + 1; i < s.length(); i++)
        {
            res *= 9;
        }
    }

    if (prevDigit != curDigit)
    {
        if (pos + 1 < s.length())
        {
            res += solver(s, pos + 1);
        }
        else
        {
            res += 1;
        }
    }

    return res;
}

void solve1()
{
    scanf("%lld%lld", &a, &b);

    printf("%lld",
        solver(to_string(b)) - (a ? solver(to_string(a - 1)) : 0)
    );
}

long long dp[20][2][11];

long long solver2(const string& s, int pos = 0, bool limit = 1, int prevDigit = 10)
{
    if (pos == 0)
    {
        memset(dp, -1, sizeof(dp));
    }

    if (pos >= s.length())
    {
        return 1;
    }

    if (dp[pos][limit][prevDigit] != -1)
    {
        return dp[pos][limit][prevDigit];
    }

    bool allZerosBefore = prevDigit == 10;

    int bound = limit ? (s[pos] - '0') : 9;

    long long res = 0;

    for (int i = 0; i <= bound; i++)
    {
        if (!allZerosBefore && i == prevDigit)
        {
            continue;
        }

        res += solver2(s, pos + 1, limit ? (i == bound) : 0, !allZerosBefore ? i : (i == 0 ? prevDigit : i));
    }

    dp[pos][limit][prevDigit] = res;

    return res;
}

void solve2()
{
    scanf("%lld%lld", &a, &b);

    printf("%lld",
        solver2(to_string(b)) - (a ? solver2(to_string(a - 1)) : 0)
    );
}

namespace Solver3 {
    auto pow9 = [](unsigned int p) -> long long {
        long long res = 1;

        for (int i = 1; i <= p; i++)
        {
            res *= 9;
        }

        return res;
    };

    long long recursionFunction(int notAllowedFirstDigit, const std::string& number, int pos) {
        if (pos >= number.length()) {
            throw std::bad_function_call();
        }

        int firstDigit = number[pos] - '0';

        // this is count of result numbers that has length (number.length() - pos)
        // and starts with digit less then firstDigit and not equals to notAllowedFirstDigit
        auto fullRests = [&]() {
            int countOfDigitsLessOrEqualToFirst = firstDigit + (1 /* this is 0 digit */);

            int numberOfFullRests = countOfDigitsLessOrEqualToFirst - (1 /*this is firstDigit*/) - (notAllowedFirstDigit < firstDigit ? 1 : 0);

            return numberOfFullRests * pow9((int)number.length() - pos - 1);
        };

        auto res = fullRests();

        if (firstDigit != notAllowedFirstDigit) {
            if ((pos + 1) == number.length()) {
                res += 1;
            } else {
                res += recursionFunction(firstDigit, number, pos + 1);
            }
        }

        return res;
    }

    long long countOfNumbersWithNoTwoSameAdjacentDigits(long long number) {
        auto strNumber = to_string(number);

        long long res = 0;

        for (int i = 0; i < strNumber.length(); i++) {
            res += pow9(i);
        }

        res += recursionFunction(0, strNumber, 0);

        return res;
    }

    void solve() {
        scanf("%lld%lld", &a, &b);

        long long rightRangeBorderRes = countOfNumbersWithNoTwoSameAdjacentDigits(b);
        long long leftRangeBorderRes = (a ? countOfNumbersWithNoTwoSameAdjacentDigits(a - 1) : 0);

        auto rangeRes = rightRangeBorderRes - leftRangeBorderRes;

        printf("%lld", rangeRes);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;
    //scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        //solve1();
        //solve2();
        Solver3::solve();
    }

    return 0;
}