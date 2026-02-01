# Permutation In String
## Keywords
- **Permutation**: same set of elements, different ordering
- **Substring**: smaller, sequential string within a larger string

## Strategy
+ **Substring** hints the use of a sliding window, from the problem, a fix-sized sliding window(i.e. there will be some "drop leftmost, include rightmost/current" actions going on).
+ **Permutation** hints the use of a hashmap to record the characters appeared and their frequencies.

## Implementation
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
## Complexities
### Space Complexity
- constant, 2 list of 26 elements and some local variables ⇒ $O(1)$
### Time Complexity
- $O(n_2)$, the algorithm has to check each letter in `s2` and see if a permutation of `s1` exists