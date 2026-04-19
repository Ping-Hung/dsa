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
|$O(n^{2})$ | $O(1)$|


## Binary Search
* Makes use of the **non-increasing** property, converting the inner loop into binary search
* `r = n2 - 1`, this initialization requirement needs to be proved.
```go
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
|$O(n_1 \log{n_2} )$ | $O(1)$|

### `r = n2 - 1` Requirement Proof
$n_1$ is the length of `nums1` and $n_2$ is the length of `nums2`, from `for i := 0; i < n1; i++`,
one could infer $l, i \in \{ 0, 1, 2, ..., n_{1} - 1 \}$.
The initialization `r = n2 - 1` is to garauntee `mid = l + (r - l) / 2` (equivalent to `mid = (l +
r) / 2`) is strictly less than `len(nums2)` to prevent out-of-bounds access.

In other words, we are trying to show the validity of the inequality given `r` is initialized to `n2 - 1`
```math
    \forall l \in \{ 0, 1, 2, ..., n_1 - 1 \}, \text{mid} = \frac{(l + r)}{2} < n_2
```

From the range of $l$, we can limit the scope of discussion to $l = \max{l} = n_1 - 1$, and 
$r = n_2 - 1$ because no values of $l$ can exceed $n_1 - 1$, and the value of $r$ can decrease after
the first iteration of binary search.

#### Case 1: $n_1 \leq n_2$
Plugging the $l$ and $r$ values into $\text{mid} = \frac{l + r}{2}$.

```math
    \begin{align*}
        n_1 \leq n_2   &\iff \\
        \frac{n_1 - 1 + n_2 - 1}{2} \leq \frac{n_2 - 1 + n_2 - 1}{2}   &\iff\\
        \frac{n_1 + n_2 - 2}{2} \leq \frac{2n_2 - 2}{2}.
    \end{align*}
```
Since the operations involved are integer divisions (the quotient is truncated integer), the above
equation could be rewritten as the following

```math
    \begin{align*}
        \frac{n_1 + n_2 - 2}{2} \leq \frac{2n_2 - 2}{2} &\iff \\
        \lfloor \frac{n_1 + n_2 - 2}{2} \rfloor \leq \lfloor \frac{2n_2 - 2}{2} \rfloor &\iff \\
        \lfloor \frac{n_1 + n_2 - 2}{2} \rfloor \leq \lfloor n_2 - 1 \rfloor &\square
    \end{align*}
```
One could see $\max \text{mid}$ is bounded above by $n_2 - 1$ when $n_1 \leq n_2$.

**Side Note**
- When we have $n_1 = n_2$, there's no need to worry `nums2[mid]` triggering out-of-bounds access,
  when one of the array is longer, above proof could justify the initialization of `r := n_2 - 1`
  (this is assuming $n_2$ is the longer array).

## Two Pointers
