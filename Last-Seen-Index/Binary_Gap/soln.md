# Problem
Find the largest binary gap of `N: int` where `N` is a 32-bit int type ranging from 0 to 2147483647.

A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

---
**Test Cases**
|input|expected output|
|---|---|
|1|0|
|2|0|
|5|1|
|8|0|
|20|1|
|73|2|
|37|22|

# Solutions
## Sliding window attempt (not the best fitting pattern)
```python
def bit_at_pos(pos: int, N: int):
    return (N & (1 << pos)) >> pos

def solution(N):
    # try sliding window from bit 0 to bit 30, examine each bit
    gap = 0
    r = 0
    # shall maintain l >= r throughout
    for l in range(31):
        if bit_at_pos(l, N) == 0:
            continue
        # now bit(l) == 1
        if bit_at_pos(r, N) == 1:
            gap = max(gap, l - r - 1)
        r = l
    return gap
```

## Last-Seen Index (According to ChatGPT)
+ Note the use of `prev`, which is a sentinel here.
  - use this to eliminate one more bit check (and is more logically sound for
  algorithm analysis)

```python
def solution(N: int) -> int:
    gap = 0
    prev = -1  # position of previous 1-bit

    for i in range(31):
        if N & (1 << i):
            if prev != -1:
                gap = max(gap, i - prev - 1)
            prev = i

    return gap
```