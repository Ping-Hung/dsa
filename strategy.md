# Interview Strategy
1. **DON'T** rush into the problem, **READ** it carefully.
    - Ensure you can clearly describle the program input and desired output in laymen's terms.
    - Read carefully and extract
        - "Input/output"
        - "Constraints": 
            - e.g. `n ≤ 20`, `n ≤ 10^5`, `n ≤ 10^6`
            - range of input is within `[min, max]`
        - Edge cases

2. Identify _ambiguities_ and _problems_, come up with initial guesses and either
    1. ask for clearification, but ask _strategically_
        - ask about 
            - duplicates
            - empty inputs
            - sortedness
            - integer overflow
        - but **avoid** asking things **already stated**
    2. try your best bet

3. Come up with simple example inputs and outputs.
    - First think of normal cases
    - Then edge cases like:
        - Empty
        - Single element
        - All identical
        - Strictly increasing
        - Strictly decreasing
        - Maximum size

4. Play around with them, visualize them by drawing, and see if there exists a
pattern.
    - **Important:** Time-box thinking to 5-10 minute range.
    - Ask these guiding questions while designing:
    > 1. How do I manipulate the input step by step to reach desired output?
    > 2. What are the essential states I need to keep track of, what data
    >    structures should be involved?
    - Before coding state expected time & space complexity.

5. **Describe** the firstest thing that comes to your mind, the most bruteforce, straight forward solution.

6. **Implement** either
    - the brute-force (if the problem has loose (or no) performance requirements.
    - the optimal solution directly (if you know how to)

7. Verify correctness by
    - Walk through own test cases
    - Simulate manually
    - Check all edge cases
    - Check off-by-one errors
    - Check integer overflow
    - **Note:** talk while testing, so interviewer can check your reasoning (if there is a human interviewer)

8. If time permits (and algorithm is correct), try reducing big O complexity of
   the algorithm by using cleverer data strcutures and algorithms

---
# Summary

## Phase 1 — Understand
- Restate problem
- Identify constraints
- Clarify ambiguities
- List edge cases   
## Phase 2 — Explore and Write/Describe rough V1
- Try small examples
- Find patterns
- Derive brute force
- Analyze complexity    
## Phase 3 — Improve
- Identify bottleneck
- Replace nested loops with:
    - Hash map
    - Prefix sum
    - Sliding window
    - Monotonic stack
    - Heap
    - DP    
## Phase 4 — Implement
- Code cleanly
- Speak your thought process    
## Phase 5 — Validate
- Run through normal test cases
- Run through Edge cases
- Complexity recap
