#include <iterator>
#include <print>
#include <string>
#include <string_view>
#include <unordered_map>

std::string minWindow(std::string s, std::string t)
{
    std::unordered_map<char, int> seen;
    for (char c : t)
        ++seen[c];

    auto left = s.cbegin();
    auto right = left;
    auto len_t = std::ssize(t);
    auto best_left = left;
    auto best_right = left;

    if (static_cast<size_t>(len_t) > s.length())
        return "";

    int missing = static_cast<int>(t.length());
    auto need = seen;

    for (; left != s.cend() - len_t + 1; ++left)
    {
        while (missing != 0 && right != s.cend())
        {
            if (need[*right] > 0)
            {
                --missing;
            }
            --need[*right];
            ++right;
        }
        if (missing == 0)
            if (best_left == best_right ||
                right - left < best_right - best_left)
            {
                best_left = left;
                best_right = right;
            }

        ++need[*left];
        if (need[*left] > 0)
        {
            ++missing;
        }
    }
    return std::string(best_left, best_right);
}

void check(std::string_view s, std::string_view t, std::string_view expected)
{
    std::string got = minWindow(std::string(s), std::string(t));
    std::println("{}  s=\"{}\" t=\"{}\" expected=\"{}\" got=\"{}\"",
                 got == expected ? "PASS" : "FAIL", s, t, expected, got);
}

int main()
{
    check("ADOBECODEBANC", "ABC", "BANC");
    check("a", "a", "a");
    check("a", "aa", "");
    return 0;
}
