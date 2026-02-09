# Problem Statement:
You are given an array of integers `cost` where `cost[i]` is the cost of taking a
step from the ith floor of a staircase. After paying the cost, you can step to
either the `(i + 1)th` floor or the `(i + 2)th` floor.

You may choose to start at the index 0 or the index 1 floor.

Return the minimum cost to reach the top of the staircase, i.e. just past the
last index in cost.

|**Input**|**Output**|
|---|---|
|`cost: int[]`| minimum cost to reach stair `len(cost) - 1`: `int`|

# Applying SRTBOT Framework
1. **Subproblem**: `min_cost[i]`:= minimum cost required to reach stair case `i`
2. **Relate** (with recursion relation): to reach level `i`, one must choose the
minimum between
`min_cost[i - 2] + cost[i - 2]` and `min_cost[i - 1] + cost[i - 1]`, more formally
```
min_cost[i] = min(min_cost[i - 1] + cost[i - 1], min_cost[i - 2] + cost[i - 2])
```
3. **Topological Order**: increasing value of `i` (we climb up from level 0 to `len(cost) - 1`)
4. **Base case**: `min_cost[0] = min_cost[1] = 0`. Per problem statement, one
could begin from either one with no cost.
5. **Original Problem**: We want to find `min_cost[n]`, which is defined by the
recurrence relation:
```
min_cost[n] = min(min_cost[n - 1] + cost[n - 1], min_cost[n - 2] + cost[n - 2])
```
6. **Time and Space analysis**: 
    + **Time complexity**: $O(n)$
        - we are climbing from level `0` to level `n`, evaluating cheapest total cost
    + **Space complexity**: $O(n)$ or $O(1)$ depending on implementation

# Implementations
## $O(n)$ Solution
+ Bottom-up DP tabulation
```python
    def minCostClimbingStairs(cost: List[int]) -> int:
        # recursive relation: 
        # dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])
        n = len(cost)
        # dp table setup; dp[i] := min. cost to reach stair i
        dp = [float("inf")] * (n + 1)
        dp[0], dp[1] = 0, 0  # cost for stair 0 and 1 are free, as defined by the problem
        # bottom up dp
        for i in range(2, n + 1):
            # "looking backwards" as the rhs of recursive relation contains i - 1, i - 2 (smaller values)
            if dp[i - 2] + cost[i - 2] < dp[i - 1] + cost[i - 1]:
                dp[i] = dp[i - 2] + cost[i - 2]
            else:
                dp[i] = dp[i - 1] + cost[i - 1]
        return dp[n]
```
## $O(1)$ Solution
+ Bottom-up DP Optimized, replace the `dp` table with local variables
```python
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        # recursive relation: 
        # dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])
        n = len(cost)
        dp_i = float("inf")
        dp_i2, dp_i1 = 0, 0  # cost for stair 0 and 1 are free, as defined by the problem
        # bottom up dp
        for i in range(2, n + 1):
            # "looking backwards" as the rhs of recursive relation contains i - 1, i - 2 (smaller values)
            dp_i = min(dp_i1 + cost[i - 1], dp_i2 + cost[i - 2] )
            dp_i2, dp_i1 = dp_i1, dp_i
        return dp_i
```
