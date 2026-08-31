# Divide and Conquer
* Process of solving a single problem by 
    1. Recognize how this problem is composed of identical but smaller subproblems.
    2. Write a recursive relation (formula) that models how smaller subproblems contributes to the
       larger problem.
    3. Define what the simplest subproblem is (base case), and how to solve it.
    4. Let the (call) stack do the work for you.
* Recursion naturally fits into this paradigm (pattern).
* Playing with smaller examples (as many as you want, as long as it inspires pattern recognition)
  helps a ton.
## Procedure (Concepts)
1. Identify the most trivial problem that can be solved
    - Usually, they could be solved at a glance ($O(1)$ time).
2. Divide the big problem into smaller problems identified in step 1
    - This step identifies repeating/similar structures that are smaller than the original problem,
      the order could be swapped with step 1.
3. Write out how a large problem is composed out of smaller problems (usually recursive formula)
