#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

namespace Solution
{

long long min(vector<int> &v)
{
    if (v.empty())
        return -1;

    long long min = LONG_LONG_MAX;
    for (int num : v)
    {
        if (num < min)
        {
            num = min;
        }
    }
    return min;
}

long long max(vector<int> &v)
{
    if (v.empty())
        return -1;

    long long max = LONG_LONG_MIN;
    for (int num : v)
    {
        if (num > max)
        {
            num = max;
        }
    }
    return max;
}

int aggressiveCows(vector<int> &stalls, int c)
{
    long long lo = 0;
    long long hi = max(stalls) - min(stalls);
    std::sort(stalls.rbegin(), stalls.rend());

    auto valid = [&](long long distance)
    {
        long long last = stalls.front();
        long long cows = 1;
        for (int i = 1; i < stalls.size(); i++)
        {
            if (abs(stalls[i] - last) >= distance)
            {
                cows++;
                last = stalls[i];
            }
        }
        return cows >= c;
    };

    while (lo <= hi)
    {
        long long mid = lo + (hi - lo + 1) / 2;
        if (valid(mid))
            lo = mid + 1;
        else
            hi = mid + 1;
    }

    return lo - 1;
}

} // namespace Solution

int main()
{
    vector<int> s1 = {1, 2, 8, 4, 9};
    int c1 = 3;
    cout << Solution::aggressiveCows(s1, c1) << "  (expected 3)\n";

    return 0;
}
// namespace Solution
