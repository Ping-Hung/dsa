# Permutation In String
## Keywords
- **Permutation**: same set of elements, different ordering.
- **Substring**: smaller, sequential (contiguous) string within a larger string.

## Strategy
+ **Substring** hints the use of a ***sliding window***, from the problem, a **fix-sized** sliding
  window(i.e. there will be some "drop leftmost, include rightmost/current" actions going on).
+ **Permutation** hints the use of a ***hashmap*** to record the characters appeared and their
  frequencies.

## Implementation
### Greg Hogg (<mark>*I favor this over NeetCode*</mark>)
```python
def letter_to_idx(letter: str) -> int:
    return ord(letter) - ord("a")

def checkInclusion(s1: str, s2: str) -> bool:
    n1 = len(s1)
    n2 = len(s2)
    if n1 > n2:
            return False
    freqs1 = [0] * 26
    freqs2 = [0] * 26
    for i in range(n1):
            # know that n1 <= n2
            freqs1[letter_to_idx(s1[i])] += 1
            freqs2[letter_to_idx(s2[i])] += 1
    # check first n1 letters
    if freqs1 == freqs2:
            return True
    # check the rest in s2, maintain a fixe sized sliding window
    # we checked from index 0 to index n1 - 1 above, next index is n1
    for i in range(n1, n2):
            # only s2 matters here (is long enough)
            freqs2[letter_to_idx(s2[i - n1])] -= 1   # drop the leftmost
            freqs2[letter_to_idx(s2[i])]      += 1   # include rightmost (current)
            if freqs1 == freqs2:
                return True
    return False
```
### NeetCode Solution
```python
def checkInclusion(self, s1: str, s2: str) -> bool:
    n1, n2 = len(s1), len(s2)
    if n1 > n2:
        return False
    # character frequencies: if the distribution of freq1 and freq2 are identical
    # that means s1 is a substring of s2.
    freqs1, freqs2 = [0] * 26, [0] * 26

    # fill in both freqs
    for i in range(n1):
        freqs1[ord(s1[i]) - ord('a')] += 1
        freqs2[ord(s2[i]) - ord('a')] += 1

    # number of letters matched in freq tables, matches = 26 signals identical distribution
    matches = 0 
    for i in range(26):
        if freqs1[i] == freqs2[i]:
            matches += 1

    l = 0
    for r in range(n1, n2):
        if matches == 26:
            return True
            
        # incoming letter
        freqs2[ord(s2[r]) - ord('a')] += 1   # letter entering window, instance increase by 1
        if freqs1[ord(s2[r]) - ord('a')] == freqs2[ord(s2[r]) - ord('a')]:
            matches += 1
        elif freqs1[ord(s2[r]) - ord('a')] + 1 == freqs2[ord(s2[r]) - ord('a')]:
            # when incoming letter makes freqs2 exactly 1 instance greater than freq1,
            # a miss match
            # this else if is required because decrement only happens when incoming letter introduces
            # a mismatch, not everytime a miss match happens
            matches -= 1

        # leaving letter 
        freqs2[ord(s2[l]) - ord('a')] -= 1   # letter leaving window, instance decrease by 1
        if freqs1[ord(s2[l]) - ord('a')] == freqs2[ord(s2[l]) - ord('a')]:
            matches += 1
        elif freqs1[ord(s2[l]) - ord('a')] - 1 == freqs2[ord(s2[l]) - ord('a')]:
            # when leaving letter makes freqs2 exactly 1 instance less than freqs1,
            # a mismatch
            matches -= 1
        l += 1

    return matches == 26
```

## Complexities
### Space Complexity
- constant, 2 list of 26 elements and some local variables ⇒ $O(1)$
### Time Complexity
- $O(n_2)$, the algorithm has to check each letter in `s2` and see if a permutation of `s1` exists
    - reminder: `len(s2) = n_2` is the length of the longer string.
- NeetCode's solution might be a little time efficient (reduction of the constant in front of $n$
  (but personally, the code is messier).
