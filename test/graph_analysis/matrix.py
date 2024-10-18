import copy
import csv
from typing import Dict, List, Set, Tuple


class Matrix:
    def __init__(self, size) -> None:
        self.size = size
        self.matrix = [[0] * self.size for i in range(size)]

    def __getitem__(self, coord: Tuple[int, int]):
        """matrix[(2,3)] || matrix[[2,3]] || matrix[2]"""
        if type(coord) is list or type(coord) is tuple :
            return self.matrix[coord[0]][coord[1]]
        elif type(coord) is int:
            return self.matrix[coord]

    def __setitem__(self, coord: Tuple[int, int], value):
        """matrix[(2,3)] || matrix[[2,3]] || matrix[2] == 5"""

        if type(coord) is list or type(coord) is tuple :
            self.matrix[coord[0]][coord[1]] = value
        elif type(coord) is int:
            self.matrix[coord] = value

    def row(self, index):
        return self.matrix[index]

    def switch(self, row_a: int, row_b: int, inplace=False):
        if inplace:
            new_matrix = self
        else:
            new_matrix = copy.deepcopy(self)
        c = copy.copy(new_matrix[row_b])
        new_matrix[row_b] = new_matrix[row_a]
        new_matrix[row_a] = c

        return new_matrix

    def transpose(self):
        """return a transposed version"""
        new_matrix = Matrix(self.size)
        for row in range(self.size):
            for column in range(self.size):
                new_matrix[(row, column)] = self[(column, row)]
        return new_matrix

    def __str__(self) -> str:
        out = ""
        for index, row in enumerate(self.matrix):
            out += f"{index} : {row}\n"
        return out

    
def tests():
    matrix = Matrix(3)
    print(matrix[(0, 0)])
    matrix[(0, 1)] = 0.1
    matrix[(0, 2)] = 0.2
    matrix[(1, 2)] = 0.3
    matrix[(2, 2)] = 0.4

    print("Init")
    print(matrix)

    print("Transpose")
    t = matrix.transpose()
    print(t)

    print("switch")
    t2 = t.switch(0, 2)
    print(t)
    print(t2)


if __name__ == "__main__":
    tests()
