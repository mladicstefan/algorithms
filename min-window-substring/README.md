## 76. Minimum Window Substring (Hard)

**Techniques:** variable-size sliding window (two pointers), frequency map, running "missing" counter, amortized analysis

**Key insight:** if [L, R] is valid, so is [L, R+1], so L and R only move forward. Each index enters and leaves the window once.

**Complexity:** O(n + m) time, O(alphabet) space

**Pitfalls:**
- Rewinding R or recopying the map each step → O(n²), TLE
- Only decrementing `need` when > 0 → spare copies not tracked
- Unsigned counts can't go negative
- Copying the best string on every improvement → MLE; store start + length instead
