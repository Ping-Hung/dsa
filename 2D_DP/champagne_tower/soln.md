# Leetcode 799. Champagne Tower (2D DP)
|Input|Output|
|:---:|:---:|
|`poured: int`| how full glass at `(query_row, query_glass)` is: `float`|
|`query_row: int`|  |
|`query_glass: int`| |

## Constraints
- `query_row`: row index, starts at 0.
    - 0 ≤ `query_row` ≤ 99 (max 100 layers)
- `query_glass`: column index, starts at 0 as well.
    - 0 ≤ `query_glass` ≤ 99 (max 100 layers)

- One glass holds exactly one glass of champagne
- Champagne "spill-over" <mark>evenly to the left and right</mark> when the
  glass that's holding it is full.  

![example](champagne_spill.png)

# Solution Plan
1. when `poured` champagne enters the tower, it flows from glass (0,0) "downwards"
towards glass (99,99) as shown below  
```
        (0,0)
        /   \
      (1,0)(1,1)
      /   \ /  \
    (2,0)(2,1)(2,2)
```
2. Looks like we could construct a 2D-DP table  
    DP  

    |0|1|2|...|99|
    |:---:|:---:|:---:|:---:|:---:|
    |0| | | | | 
    |1| | | | | 
    |2| | | | | 
    |...| | | | |
    |99| | | | |

3. By trying out examples (only 3 layers is enough), one could notice
    - For a glass at `(i,j)`, its overflow/spill amount is either 0 or `DP[i][j] - 1`
    - It only flows downwards, so

```
    overflow := max(0, DP[i][j] - 1)
    DP[i + 1][j] += overflow / 2
    DP[i + 1][j + 1] = overflow / 2
```



# Chat Suggestions/Tutorial
https://chatgpt.com/share/69913653-57dc-800f-ae3e-00c01c105d17
