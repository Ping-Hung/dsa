# Problem
You are given a 9 x 9 Sudoku board board. A Sudoku board is valid if the following rules are followed:  
* Each row must contain the digits 1-9 without duplicates.
* Each column must contain the digits 1-9 without duplicates.
* Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without duplicates.

Return true if the Sudoku board is valid, otherwise return false
## Constraint
* `board.length == 9`
* `board[i].length == 9`
* `board[i][j] is a digit 1-9 or '.'`.

## Constraint

## Desired Complexities
|Time|Space|
|:---:|:---:|
|$O(n^2)$|$O(n^2)$|

# Guiding Questions: Use Them to Build Solution Step by Step
1. What needs to be tracked? How can tracking be done?
> ~~the board~~ digit `1` to `9` for row, column, 3x3 grids.
> 1) one hashmap, set back to zero after each scan (row → col → square)
> 2) three hashmaps, designed specifically for row scan, column scan, square scan
>   - key from each map ranges from `0` to `8` (book-keeping board)
>   - The value of the map is a set (eliminate duplicates)
2. What is a *plausible shape* of a solution?
> notice one needs to check all $9 \times 9$ ($n^2$) squares, so shall be a "flavor" of nested loop.
3. Does this solution work? **Is it correct**?
> A thorough scan of the board looks over all squares, will be correct if the checking logic is
> programmed correctly
4. How can this solution be improved (in terms of time and space)?
> From scanning 3 passes to *1* scan only, using a more sophisticated data structure.
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

* Using 3 seperate hash sets to track seen digits.

```python
def isValidSudoku(board: List[List[str]]) -> bool:
        # row major scan
        for r in range(9):
            seen = set() 
            for c in range(9):
                if board[r][c] == '.':
                    continue
                if board[r][c] in seen:
                    return False
                seen.add(board[r][c])
        # col major scan
        for r in range(9):
            seen = set() 
            for c in range(9):
                if board[c][r] == '.':
                    continue
                if board[c][r] in seen:
                    return False
                seen.add(board[c][r])

        # iterate over each 3 x 3 square (in row major order)
        # 0 1 2          (0,0) (0,3) (0,6)
        # 3 4 5     →    (3,0) (3,3) (3,6)
        # 6 7 8          (6,0) (6,3) (6,6)
        for square in range(9):
            seen = set()
            r = 3 * (square // 3)
            c = 3 * (square % 3)
            for i in range(r, r+3):
                for j in range(j, j+3):
                    if board[i][j] == '.':
                        continue
                    if board[i][j] in seen:
                        return False
                    seen.add(board[i][j])
    return True
```

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
        cols = defaultdict(set) # str → (int, int)
        rows = defaultdict(set) # str → (int, int)
        squares = defaultdict(set) # (int, int) → (int, int)

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

