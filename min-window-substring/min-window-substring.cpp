#include <print>
#include <string>
#include <string_view>
#include <unordered_map>

std::string minWindow(std::string s, std::string t) { return ""; }

void check(const std::string &s, const std::string &t,
           const std::string &expected)
{
    std::string got = minWindow(s, t);
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
