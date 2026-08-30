# Problem

## Constraint

## Desired Complexities
|Time|Space|
|:---:|:---:|
|$O(n^2)$|$O(n^2)$|

# Guiding Questions: Use Them to Build Solution Step by Step
1. What needs to be tracked?
> ~~the board~~ digit `1` to `9` for row, column, 3x3 grids.
2. What is a *plausible shape* of a solution?
> notice one needs to check all $9 \times 9$ ($n^2$) squares, so shall be a "flavor" of nested loop.
3. Does this solution work? **Is it correct**?
4. How can this solution be improved (in terms of time and space)?

# Solution

## "Brute force" (Intuitive)
1. Scan each row and verify no duplicate digits from `1 ~ 9`.
2. Scan each column and verify no duplicate digits from `1 ~ 9`.
3. Scan each 3 $\times$ 3 grid and verify no duplicate digits from `1 ~ 9`.

## Cleaner Version
* Scan the 9 x 9 board only once, but use 3 dictionaries to book-keep seen digits.
* Note that the original 9 x 9 board is "transformed"/"re-encoded" to a 3 x 3 grid as shown below.

original:
|0|1|2|3|4|5|6|7|8|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|1 | | | | | | | | |
|2 | | | | | | | | |
|3 | | | | | | | | |
|4 | | | | | | | | |
|5 | | | | | | | | |
|6 | | | | | | | | |
|7 | | | | | | | | |
|8 | | | | | | | | |

transformed:  
|0|1|2|
|:---:|:---:|:---:|
|1| | |
|2| | |
|3| | |


```python
def isValidSudoku(board: List[List[str]]) -> bool:
        # Each of these dictionaries has key: int, value: set.
        # Every key from each dictionary ranges from 0 to 8 (range(9)) due to tracking a single 9x9 sudoku board.
        cols = defaultdict(set)
        rows = defaultdict(set)
        squares = defaultdict(set)

        for r in range(9):
            for c in range(9):
                if board[r][c] == ".":
                    continue
                if ( board[r][c] in rows[r]
                    or board[r][c] in cols[c]
                    or board[r][c] in squares[(r // 3, c // 3)]):
                    return False

                cols[c].add(board[r][c])
                rows[r].add(board[r][c])
                squares[(r // 3, c // 3)].add(board[r][c])

        return True
```

