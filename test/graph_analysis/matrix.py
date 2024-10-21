import copy
import csv
from typing import Dict, List, Set, Tuple


class RowInfo:
    def __init__(self) -> None:
        self.component = ""
        self.group = ""
        self.row_index = -1


class Matrix:
    def __init__(self, size) -> None:
        self.size = size
        self.matrix = self.get_new_matrix(self.size, fill=None)

        self.indecies = list(range(size))

    @staticmethod
    def get_new_matrix(size, fill=None):
        return [[fill] * size for i in range(size)]

    def iterate_index(self):
        """for row, column in matrix.iterate_index()"""
        for row in range(self.size):
            for column in range(self.size):
                yield (row, column)

    def iterate_values(self):
        """
        for row, column, value in matrix.iterate_index(),
        returns a copy of the matrix
        """
        m = copy.deepcopy(self.matrix)
        for row in range(self.size):
            for column in range(self.size):
                yield (row, column, m[row][column])

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

    def _switch_index(self, a: int, b: int):
        c = copy.copy(self.indecies[b])
        self.indecies[b] = self.indecies[a]
        self.indecies[a] = c

    def switch_row(self, a: int, b: int, inplace=False):
        new_matrix = self._get_instance(inplace)

        c = copy.copy(new_matrix[b])
        new_matrix[b] = new_matrix[a]
        new_matrix[a] = c

        new_matrix._switch_index(a, b)

        return new_matrix

    def transpose(self, inplace=False):
        """return a transposed version"""
        new_matrix = self._get_instance(inplace)

        for row, column, value in self.iterate_values():
            new_matrix[(column, row)] = value
        return new_matrix

    def switch_row_and_column(self, a: int, b: int, inplace=False):
        new_matrix = self._get_instance(inplace)
        new_matrix = new_matrix.switch_row(a, b, inplace=True)
        new_matrix = new_matrix.transpose(inplace=True)
        new_matrix = new_matrix.switch_row(a, b, inplace=True)
        new_matrix = new_matrix.transpose(inplace=True)
        new_matrix._switch_index(a, b)
        return new_matrix

    def set_order(self, order, inplace = False):
        new_matrix = self._get_instance(inplace)
        # print(f"Order : {order}")
        for search_pos, search_value in enumerate(order[:-1]):
            # print(f"search_value : {search_value} -> {search_value}")

            position = [found_pos for found_pos, found_value in enumerate(new_matrix.indecies) if search_value == found_value][0]
            # print(f"position : {position}")
            if(search_pos != position):
                new_matrix = new_matrix.switch_row_and_column(position, search_pos, inplace=inplace)
                print(new_matrix.indecies)

        return new_matrix

    def get_rating(self):
        r = self.get_new_matrix(self.size, 0)
        rating = 0
        
        for row, column, value in self.iterate_values():
            factor = ((self.size - row) + (column + 1)) ** 3
            if value:
                rating += factor * value
                r[row][column] = factor * value
        # print("Matrix")
        # for row in r:
        #     print(row)

        print(rating)
        return rating

    def __str__(self) -> str:
        out = f"Indecies :{self.indecies}\nMatrix:\n"
        for index, row in zip(self.indecies, self.matrix):
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

    print("switch row")
    s1 = t.switch_row(0, 2)
    print(t)
    print("S1")
    print(s1)

    print("Switch_both")
    s2 = s1.switch_row_and_column(0, 1)
    print(s2)

    print("reorder")
    order = [2,3,1,0]
    s3 = s2.set_order(order, inplace=False)
    print("results")
    print(s3.indecies)
    print(s3)


    matrix2 = Matrix(4)
    matrix2[(0, 1)] = 1
    matrix2[(0, 2)] = 1
    matrix2[(1, 2)] = 1
    matrix2[(2, 2)] = 1

    print(matrix2)
    print(matrix2.get_rating())



if __name__ == "__main__":
    tests()
