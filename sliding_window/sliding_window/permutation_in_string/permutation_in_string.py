from collections import Counter
print(any([1,0,1]))	# true if any element in iterable is non-zero
print(all([1,0,1])) # true if all elements in iterable is non-zero

def letter_to_idx(letter: str) -> int:
    return ord(letter) - ord("a")

# Permutation := same letters, different order
#  - map letters to their frequency
# Substring := sequential subsection of a string
#   - Sliding window (fixed size in this example)
#   - Fix sized sliding window: 
#      - loose 1 on left while gain 1 on right (if going right, and vice versa)

# window: [i - n1 + 1, i]; 
# invariant: 
#   1. at any iteration i, freqs2 tracks character count in s2[i - n1, i]
#   2. freqs2 == freqs1 iff a permutation of s1 exists in s2
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


s1 = "abc"
s2 = "lecabee"

print(checkInclusion(s1, s2))
