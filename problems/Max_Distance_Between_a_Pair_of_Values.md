# Problem Statement
You are given two non-increasing 0-indexed integer arrays `nums1` and `nums2`.

A pair of indices `(i,j)`, where `0 <= i < nums1.length` and `0 <= j < nums2.length`, is **valid** *if both `i <= j` and `nums1[i] <= nums2[j]`*. The **distance of the pair** is *`j - i`*.

Return the maximum distance of any valid pair `(i, j)`. If there are no valid pairs, return `0`.

An array arr is <mark>**non-increasing**</mark> if `arr[i-1] >= arr[i]` for every `1 <= i < arr.length.`

# Constraints
- `1 <= nums1.length, nums2.length <= $10^{5}$`.
- `1 <= nums1[i], nums2[i] <= $10^{5}$`.
- Both `nums1` and `nums2` are **non-increasing**.

# Observations / Identities
* the **non-increasing** property ensures both `nums1` and `nums2` are sorted in descending order.
    - sorted sequence/array hints plausible use of binary search.


# Solutions
## Brute Force
* Trivial nested `for` loops. Exceeds permitted time constraint
```go
func maxDistance(nums1 []int, nums2 []int) int {
    // brute force
    var (
        dist int = 0
        n1 int = len(nums1)
        n2 int = len(nums2)
    );

    for i := 0; i < n1; i++ {
        for j := i; j < n2; j++ {
            if nums1[i] <= nums2[j] {
                dist = max(dist, j - i);
            }
        }
    }

    return dist;
}
```

|Time complexity | Space Complexity |
|:---:|:---:|
|$O(n^{2})$ | $O()$|


## Binary Search
* Makes use of the **non-increasing** property, converting the inner loop into binary search
* `r = n2 - 1`, this initialization requirement needs to be proved.
```=go
func maxDistance(nums1 []int, nums2 []int) int {
    var (
        dist int = 0
        n1 int = len(nums1)
        n2 int = len(nums2)
    );
    for i := 0; i < n1; i++ {
        var (
            l int = i
            r int = n2 - 1 // this is needed (to prevent out-of-bounds, to be proved!)
            mid int
        );
        // find the *furthest* value (nums2[mid]) smaller than nums1[i]
        // Using binary search (both nums1 and nums2 are sorted non-increasingly)
        for l <= r {
            mid = l + (r - l) / 2;
            if nums2[mid] >= nums1[i] {
                dist = max(dist, mid - i);
                l = mid + 1
            } else {
                r = mid - 1
            }
        }
    }

    return dist;
}
```
|Time complexity | Space Complexity |
|:---:|:---:|
|$O(n1 \log{n2} )$ | $O(1)$|

### `r = n2 - 1` Requirement Proof
$n_1$ is the length of `nums1` and $n_2$ is the length of `nums2`, from loop initialization

## Two Pointers
