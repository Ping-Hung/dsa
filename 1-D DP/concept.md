# Concepts and Mental Model
> DP is about solving problem with overlapping subproblems.
## The SRTBOT Framework
1. **Subproblem** definition
    + Describe the meaning of subproblem in <mark>**words**</mark>, in terms of input
    parameters
    + Subproblems usually lie in <mark>**subsets of input**</mark>
        - e.g. prefix, suffix, running (continuous) substring of a sequence
    + Subproblems usually record <mark>partial state</mark> (of the entire solution):
        - could add subproblems by incrementing some auxiliary variables.
2. **Relate** subproblem solutions recursively
    + look for recursive relation between subproblems
    + DP recurrence must satisfy:
        > 1. define **only one** state at a time
        > 2. decisions must be made by comparing **complete subproblem solutions**
         instead of local costs.
3. **Topological order** on subproblems
    + For arguing relation is _acyclic_ and _subproblems form a DAG_
4. **Base** cases of relation
    + Solution to ultra simple cases (for all reachable subproblems) when
    recursion (or dependency on subproblems) is not needed
5. **Original** problem solution via subproblem(s)
    + Show how the original problem could be solved by reusing solutions to subproblem(s)
6. **Time** and space analysis
* Source: MIT 6.006 Introduction to Algorithms

# Greg Hogg's DP Approach
> recursive backtrack -> top-down memoization -> bottom-up tabulation -> bottom-up without table (or only partial table)
* source: https://www.youtube.com/shorts/uUjFL0C-vY0?feature=share


# How to Verify Recursion
Pause and ask these guiding questions (assume _f(x)_ is the recursive function):
1. _What exactly does f(x) mean?_
2. _Do my base cases match reality?_
3. _What is the last decision?_
4. _Are the subproblems disjoint and complete?_
5. _Does this match small hand-calculated cases?_

# Cache/Memoization Notes:
1. _Cache/Memo only remembers <mark>past computation</mark>, which are computed by recursion._
2. _Memoization stores answers to states, not transitions between states._
