from typing import List
def spiral_order(matrix: List[List[int]]) -> List[int]:
    spiral: List[int] = []
    def fillin(r: int, c: int, dr: int, dc: int, m: int, n: int) -> None:
        """
            r, c: starting location
            dr, dc: direction of matrix traversal
            m, n: matrix dimension
        """
        if m == 0 or n == 0:
            return
        for _ in range(n):
            r += dr
            c += dc
            spiral.append(matrix[r][c])
        fillin(r, c, dc, -dr, n, m - 1)

    fillin(0, -1, 0, 1, len(matrix), len(matrix[0]))
    return spiral

m = [[1]]
print(spiral_order(m))


m = [[1, 2]]
print(spiral_order(m))


m = [[1], [2]]
print(spiral_order(m))

m = [[1, 2], [3, 4]]
print(spiral_order(m))

m = [[1, 2, 3], [4, 5, 6]]
print(spiral_order(m))

m = [[1, 2], [3, 4], [5, 6]]
print(spiral_order(m))
