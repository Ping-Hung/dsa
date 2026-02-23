# Problem
Given a binary string `s` and an integer `k`, return true if every binary code
of length `k` is a substring of `s`. Otherwise, return false.

|Input|Output|
|:---|:---|
|`s`: `string`| `true`: all $2^k$ bit patterns appeared as k-length substrings in `s`|
|`k`: `int`| `false`: not all $2^k$ bit patterns appeared as k-length substrings in `s`|

# Solution
1. Brute-Force:
    > 1. Generate $2^k$ patterns
    > 2. Check all `k` substrings in `s` for every bit pattern
    - Time complexity: $O(2^k * k * n)$
2. Can I scan `s` once and gather information of all $2^k$ patterns?
    - Keep track of:
        1. Seen patterns
        2. Substring length
        3. Value of current substring (seen pattern array indexing)

# Implementation
```c
#define MAX_PATTERNS 1U << 20
bool hasAllCodes(char* s, int k) 
{
    // there are 2^k possible patterns
    bool pattern[MAX_PATTERNS] = { false };  // pattern[0b101] = pattern[5] := is 5 seen?
    int code_val = 0;
    int s_len = strlen(s);
    // scan through s, book-keeping seen patterns
    int l = 0;
    for (int r = 0; r < s_len; r++) {
        code_val = 2*code_val + (s[r] - '0');
        if (r - l + 1 == k) {
            if (code_val == 0) {
                pattern[0] = true;
                code_val = 0;
            } else if (code_val < 0) {
                printf("unexpected overflow by k's constraint\n");
                exit(1);
            } else {
                pattern[code_val] = true;
                // code_val -= 2^(k - 1) * (s[l] - '0')
                code_val -= (1 << (k - 1)) * (s[l] - '0');
            }
            l += 1;
        }
    }
    // if every pattern is seen, return true, else false
    bool res = true;
    for (int i = 0; i < (1 << k); i++) {
        res &= pattern[i];
    }
    return res;
}
```
# Time Complexity: $O(n + 2^k)$
- Cost of scanning + cost of checking all patterns seen

# Space Complexity: $O(k)$
- Although not implemented, can actually allocate `k` elements for the
  `pattern` array on the heap with `calloc`

# Potential Improvement
- Use a variable to keep track of how many patterns seen: this eliminates the final loop
    - Time complexity becomes $O(n)$
- Use bit operations like masking, ORing, and shifting to replace addition and
  multiplication.

## Improved Implementation
```c
#define MAX_PATTERNS 1U << 20   // there are 2^k possible patterns 
/* usage: pattern[0b101] = pattern[5] := is 5 seen? */
bool pattern[MAX_PATTERNS] = { false };  

bool hasAllCodes(char* s, int k) {
    unsigned code_val = 0;
    int s_len = strlen(s);
    int pattern_seen = 1 << k;

    /* scan through s, book-keeping seen patterns */ 
    int l = 0;
    unsigned mask = pattern_seen - 1;   /* do this to keep the lower k bits (for safety on large inputs) */
    for (int r = 0; r < s_len; r++) {
        code_val = ((code_val << 1) & mask) | (s[r] - '0');
        if (r - l + 1 == k) {
            if (!pattern[code_val]) {
                pattern[code_val] = true;
                pattern_seen--; /* mark **unique** patterns seen thus far */
            }
            /* prep for next iter: unset (turn off) the kth (highest order) bit */
            code_val &= ~(1 << (k - 1));
            l += 1;
        }
    }
    /* if all pattern are seen/present, return true, else false */
    return pattern_seen == 0;
}
```
