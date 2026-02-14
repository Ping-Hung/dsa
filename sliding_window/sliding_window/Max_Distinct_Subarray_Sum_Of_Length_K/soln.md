# Problem
You are given an integer array `nums` and an integer `k`. Find the maximum subarray sum of all the subarrays of `nums` that meet the following conditions:    
    - The length of the subarray is `k`, and
    - All the elements of the subarray are distinct.

Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return 0.

> A subarray is a contiguous non-empty sequence of elements within an array.

# Solution
## Observations
|Input|Output|
|:---:|:---:|
|`nums:List[int]` | maximum sum of a subarray that has size `k` and only contains unique elements|
|`k: int` |ø|

- **Distinct numbers**: have to keep track of seen elements
- **Subarray sum**: 
    - most optimal way:
        - scan `nums` once, then
        - return the subarray sum.
    - have to keep track of current sum and window size

## State(s) to Keep Track
- Seen elements: a hashmap or an array
- Current sum: one single variable
- window size: `l` and `r` indeces of the window
    - window size := `r - l + 1`

## Algorithm: Sliding-Window

## Implementation
```c
long long maximumSubarraySum(int* nums, int numsSize, int k) {
    int seen[100000] = { 0 };  // seen elements; index from 0 to 10^5 - 1
    long long max_sum = 0;
    long long curr_sum = 0;
    
    /*
    * solving with sliding window:
    *  window := closed interval between l and r, satisfying:
    *  1) r - l + 1 <= k
    *  2) all elements in window are unique*/
    int l = 0;
    for (int r = 0; r < numsSize; r++) {
        // augment current value
        seen[nums[r] - 1] += 1;
        curr_sum += nums[r];
        while (r - l + 1 > k || seen[nums[r] - 1] > 1) {
            // correct window when invariant is violated
            seen[nums[l] - 1] -= 1;
            curr_sum -= nums[l];
            l++;
        }
        if (r - l + 1 == k) {
            max_sum = max_sum >= curr_sum ? max_sum : curr_sum;
        }
    }
    return max_sum;
}
```

# Complexity Analysis
## Time Complexity: $O(n)$
- look through the list once and return the sum.
## Space Complexity: $O(n)$
- The `seen` array/hashmap size is proportional to the number of elements in `nums`.
