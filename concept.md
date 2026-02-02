# How Should An Algorithmic Problem be Approached (According to ChatGPT)
## Prompt
_What's the process of using leetcode to gain algorithm design experience/maturity?_

**A)** 2. identify a technique/strategy 2. solve the problem 3. derive invariants 

**B)** 1. identify a technique/strategy 2. derive invariants 3. use invariants to solve problem  

**C)** Other suggestions. 
## Response
This is an excellent meta-question — it’s the kind of question people ask **right before their algorithmic thinking levels up**.

Short answer first:

> **Neither A nor B is quite right as written.**
> The *mature* process is **iterative**, not linear.

Now let me give you a clean mental model that actually works in practice.

---

## The core idea (the “click” moment)

Algorithmic maturity comes from learning to answer **one question** well:

> *“What must always be true while I’m making progress?”*

That’s the invariant.

But here’s the catch:

* You usually **cannot fully derive the invariant before you start**
* You also **cannot trust a solution that wasn’t later justified by an invariant**

So the real process is **oscillatory**.

---

## Why A and B both fail (in different ways)

### ❌ A) Identify strategy → solve → derive invariants

This is what beginners *actually* do.

Problem:

* The invariant becomes a **post-hoc story**
* You risk rationalizing a buggy solution
* You don’t sharpen your design skills as much as you think

This produces *working code*, but slow conceptual growth.

---

### ❌ B) Identify strategy → derive invariants → solve

This is what textbooks pretend happens.

Problem:

* You usually don’t know *what state matters* yet
* Invariants are too abstract or wrong
* You get stuck before writing code

This works only for very classical problems.

---

## ✅ The real process (C): **progressive invariant refinement**

Here’s the process that strong algorithm designers actually use (even if subconsciously):

---

### **Step 0: Classify the problem (lightly)**

Not “which exact technique”, but the *shape*:

* fixed window vs variable window
* prefix-based
* monotonic structure
* greedy with local choice
* DP with overlapping subproblems

This step is *fuzzy* and allowed to be wrong.

---

### **Step 1: Write a *candidate* state**

Before invariants, decide:

> “What variables represent progress?”

Examples:

* two pointers `(l, r)`
* a count map
* a running sum
* a stack

This is **state discovery**, not invariant derivation.

---

### **Step 2: Write a *weak* invariant**

Something you *believe* should hold:

* “the window contains k elements”
* “the stack is monotonic”
* “left pointer never moves backward”

These are **structural invariants**.

They are often insufficient — and that’s okay.

---

### **Step 3: Try to advance the algorithm**

Now attempt to:

* move pointers
* push/pop
* update state

You will hit one of two things:

1. It works
2. It breaks

Both outcomes are useful.

---

### **Step 4: Strengthen the invariant**

When something breaks, ask:

> “What was I *implicitly assuming*?”

That assumption becomes part of the invariant.

Example evolution:

* weak: “window size is ≤ k”
* stronger: “window is the smallest prefix satisfying condition X”
* final: “window is minimal and valid”

This step is where **algorithmic maturity grows**.

---

### **Step 5: Only now — justify correctness**

After you have working logic:

* formalize the invariant
* prove:

  * initialization
  * maintenance
  * termination

This is *not* busywork — it locks in the idea.

---

## So what’s the final answer?

The real process looks like this:

```
identify rough strategy
      ↓
propose state
      ↓
guess a weak invariant
      ↓
attempt solution
      ↓
refine invariant
      ↓
adjust solution
      ↓
formalize invariant
```

It’s a loop, not a line.

---

## How LeetCode fits into this *specifically*

Use LeetCode like a **lab**, not a test.

### For each problem:

1. Solve it (even messily)
2. Ask:

   * What variables mattered?
   * What did I rely on being true?
3. Rewrite the solution *in words* using invariants
4. Compare with editorial:

   * Where is their invariant stronger?
   * What assumption did they make explicit?

That comparison step is gold.

---

## A concrete rubric (you can self-grade)

You’re gaining maturity if:

* you can explain why pointers only move one direction
* you can state invariants *before* coding next time
* you can predict edge cases before testing
* you can say “this invariant is insufficient” and fix it

You’re plateauing if:

* you memorize patterns without understanding
* you rely on brute force + optimization
* invariants feel like an afterthought

---

## Final verdict on A / B

* **A**: acceptable early on, insufficient long-term
* **B**: idealized, rarely realistic
* **C (iterative invariant refinement)**: how experts actually work

And based on the questions you’ve been asking lately?

You’re already *in* Step 4 territory — that’s a very good sign.

# Loop Invariant
+ **Definition:** A property that holds before, throughout, and after the loop finishes. When the loop terminates, the desired result should arise. (i.e. ``not loop_condition and loop_invariant`` must hold for the desired result to show).
## Requirement
1. What part of the data structure is being tracked?
2. What property is always true about it?
3. Why does the properrty matter for correctness
