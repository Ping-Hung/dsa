# Longest Consecutive Sequence
|Input|Output|
|:---:|:---:|
|`nums: List[int]`|`length: int`|

Given an integer list `nums`, return the length of the longest *consecutive sequence* existed in the
list. A *consecutive sequence* is a sequence of numbers `nums[c1], nums[c2], nums[c3],...` such that 
`nums[c1] + 1 = nums[c2]`, `nums[c2] + 1 = nums[c3]`,... . **You must write an algorithm that runs
in $O(n)$ time**.

## Constraints
1. 0 ≤ `len(nums)` ≤ $10^6$
2. $-10^9$ ≤ `nums[i]` ≤ $10^9$

# Guiding Questions
1. Does duplicates exist in `nums`?
> Yes, but the focus needs to be *length* of longest *consecutive sequence*.
2. What needs to be tracked?
> ~~seen elements~~, **Unique elements** and the length of sequence.

# Key Point/Observations:
* When scanning an array, we are processing *one element* at a time.
* Every element could be the beginning of a *consecutive sequence*.
* <mark>an element `n` in `nums` is a candidate for **beginning of sequence** iff `n - 1` is **NOT**
  in `nums`</mark>
* Shall aim for a variant of the **linear scan** algorithm that checks each valid **start** of
  subsequence.

# Solution
```python
    def LengthLongestConsequtiveSequence(nums: List[int]) -> int:
        nums = set(nums)    # remove duplicates
        length = 0
        for n in nums:  # set elements cannot be accessed using subscripts (array indeces)
            if not n - 1 in nums:
                end = n
                while end + 1 in nums:
                    end += 1
                # (After while loop) [nums, end] is the sequence, length is thus end - n + 1
                length = max(length, end - n + 1)
        return length
```


