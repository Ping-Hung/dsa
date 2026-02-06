# Concept:
* DP is about solving problem with overlapping subproblems.

# DP Approach 1
> recursive backtrack -> top-down + memoization -> bottom-up + memoization (a.k.a tabulation) -> bottom-up without memo.
* source: https://www.youtube.com/shorts/uUjFL0C-vY0?feature=share

# How to Verify Recursion
Pause and ask these guiding questions (assume _f(x)_ is the recursive function):
1. _What exactly does f(x) mean?_
2. _Do my base cases match reality?_
3. _What is the last decision?_
4. _Are the subproblems disjoint and complete?_
5. _Does this match small hand-calculated cases?_

# Cache/Memoization Notes:
1. _Cache/Memo only remembers ==past computation==, which are computed by recursion._
2. _Memoization stores answers to states, not transitions between states._