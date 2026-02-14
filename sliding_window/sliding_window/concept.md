# Tips for Sliding Window
## Core Structure
1. Window Expansion
  + Usually book-keep (add in) a newly seen element.
2. Window Repair (when window invariant/contract breaks)
  + If newly seen element breaks invariant (e.g. introduces duplicate), shrink (usually) the left pointer.
3. Answer/Result Update
  + (usually) Do this when invariant holds.
### Summary:
Sliding window has a process of 
```
Expand right → repair by moving left → read answer when valid
```
## Caveat: It's not Universal
+ **Test:** ask "When my window becomes invalid, can i _always fix it_ by moving the left pointer forward?"
  - If yes, sliding window applies

### Requirements for Applying This Structure
1. **The Window can be defined, and it is contiguous**
  - if the interval `[l...r]` cannot be difined, no sliding window
2. **State can be updated incrementally**
  - Ensure the following capabilities:
    + adding one element
    + removing one element
    + maintain validity in $O(1)$ or amortized $O(1)$
