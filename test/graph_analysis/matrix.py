import copy
import csv
from typing import Dict, List, Set, Tuple


class Matrix:
    def __init__(self, size) -> None:
        self.size = size
        self.matrix = [[None] * self.size for i in range(size)]

    def iterate_index(self):
        """for row, column in matrix.iterate_index() """
        for row in range(self.size):
            for column in range(self.size):
                yield (row, column)

    def __getitem__(self, index):
        """matrix[(2,3)] || matrix[[2,3]] || matrix[2]"""
        if type(index) is list or type(index) is tuple:
            return self.matrix[index[0]][index[1]]
        elif type(index) is int:
            return self.matrix[index]

    def __setitem__(self, index, value):
        """matrix[(2,3)] || matrix[[2,3]] || matrix[2] == 5"""

        if type(index) is list or type(index) is tuple:
            self.matrix[index[0]][index[1]] = value
        elif type(index) is int:
            self.matrix[index] = value

    def row(self, index):
        return self.matrix[index]

    def _get_instance(self, inplace=False):
        if inplace:
            return self
        else:
            return copy.deepcopy(self)

    def switch_row(self, a: int, b: int, inplace=False):
        new_matrix = self._get_instance(inplace)

        c = copy.copy(new_matrix[b])
        new_matrix[b] = new_matrix[a]
        new_matrix[a] = c

        return new_matrix

    def transpose(self):
        """return a transposed version"""
        new_matrix = copy.deepcopy(self)

        for row, column in self.iterate_index():
            new_matrix[(row, column)] = self[(column, row)]
        return new_matrix
    
    def switch_row_and_column(self, a: int, b: int, inplace=False):
        new_matrix = self._get_instance(inplace)
        new_matrix = new_matrix.switch_row(a, b, inplace=True)
        new_matrix = new_matrix.transpose()
        new_matrix = new_matrix.switch_row(a, b, inplace=True)
        new_matrix = new_matrix.transpose()
        return new_matrix

    def __str__(self) -> str:
        out = ""
        for index, row in enumerate(self.matrix):
            out += f"{index} : {row}\n"
        return out

def tests():
    matrix = Matrix(4)
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
    t2 = t.switch_row(0, 2)
    print(t)
    print("T2")
    print(t2)

    print("Switch_both")
    s1 = t2.switch_row_and_column(0, 1)
    print(s1)


if __name__ == "__main__":
    tests()
