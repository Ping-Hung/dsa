# ClimbStairs
You are ==**Given**== an integer n representing the number of steps to reach the top of a staircase. You can climb with either 1 or 2 steps at a time.

==**Return**== the number of distinct ways to climb to the top of the staircase.

# Solution
* A simple 1-D DP problem, solution approach
> **recursive backtrack** -> **top-down memoization** -> **bottom-up tabulation** -> **bottom-up optimized (perhaps w/o entire table)**

# Step 1: Recursive Backtrack
* Note _for any n stairs ahead, one could climb to the top by taking 1 step or 2 steps at a time_
> A.K.A steps of size 1 and steps of size 2 contributes to current "height" of n
* Recursive relation: 
`steps[n] = steps[n - 1] + steps[n - 2]`

## Code
```python
  def climbStairs(n: int) -> int:
      if n <= 1:
          return 1
      return climbStairs(n - 1) + climbStairs(n - 2)
```
* Side note: this relation is exactly the Fibonacci Sequence

# Step 2: Top-Down DP + Memoization
* Q: What are some compuation I could eliminate by saving a copy to use later?
  A: We want to build our solution by sequence `n → n - 1 → ... → 1`, so let's try to store `steps[0]`, `steps[1]`, ... ,`steps[n - 2]`, `steps[n - 1]`.
* A dictionary naturally fits into the scenario.
* **Remember:** Recursion computes values, memoization only stores the value

## Code
```python
    memo = {0: 1, 1: 1}
    def climbStairs(n: int) -> int:
        if not n in memo:
            memo[n] = climbStairs(n - 2) + climbStairs(n - 1)
        return memo[n]
```

# Step 3: Bottom-Up DP (Tabulation)
* Fill-in the table from the "bottom" of n-stairs (stair 0) to the "top" (stair n).
## Code
```python
  def climbStairs(n: int) -> int:
      memo = {0: 1, 1: 1}
      for i in range(2, n + 1):
          memo[i] = memo[i - 1] + memo[i - 2]
      return memo[n]
```

# Step 4: Bottom-Up DP (Optimized without explicit table)
* From Step 3, noticed that only 2 values from the table is needed to compute the number of ways to reach step i, i ∈ [2, n]. Thus, `memo`, the dictionary is replaced with variables `n1` and `n2`

## Code
```python
  def climbStairs(n: int) -> int:
      n1, n2 = 1, 1
      ways = 1 
      for i in range(2, n + 1):
          ways = n1 + n2
          n1, n2 = n2, ways
      return ways
```

# ChatGPT Conversation that Helps
- https://chatgpt.com/share/698581b6-74fc-800f-9b81-f65c8b6bde67
