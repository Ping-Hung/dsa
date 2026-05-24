# 239. Sliding Window Maximum
You are given an array of integers `nums` and an integer `k`. There is a sliding window of size `k`
that starts at the left edge of the array. The window slides one position to the right until it
reaches the right edge of the array.

Return a list that contains the maximum element in the window at each step.

|Input|Output|
|------------------|------|
|`nums: List[int]` | `result: List[int]`|
|`k: int`          |                    |


# Constraints
+ `1 <= nums.length <= 100,000`
+ `-10,000 <= nums[i] <= 10,000`
+ `1 <= k <= nums.length`

# Keywords and Observations
+ Max of `k` ints
    + What's an efficient way to find max. of `k` ints?
        + ~~Binary search?~~: requires the window to be sorted, but the problem doesn't garauntee
          this.
        + max heaps?:
            - Heapify each window: $O(k)$, find largest: $O(1)$
            - Might require a seperate array of size `k` for the heap
                - Simple heapify of `[l...r]` might be possible
        + modified version of linear scan, using `prevMax` and `currMax`
            - Might have $O(k)$ complexity if done right.
+ Sliding window: Fix-sized
    + will be doing "including 1 element, excluding 1 element" after the first `k`-element window.
