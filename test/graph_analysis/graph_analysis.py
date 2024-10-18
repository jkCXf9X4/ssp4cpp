import copy
import csv
from typing import Dict, List, Self, overload


class DoubleMap:
    def __init__(self) -> None:
        self.map = {}
        self.inv_map = {}

    def add(self, key, value):
        self.map[key] = value
        self.inv_map[value] = key
        assert len(self.map) == len(self.inv_map)

    def get_value(self, key):
        return self.map[key]

    def get_key(self, value):
        return self.inv_map[value]

    def get_length(self):
        return len(self.map)

    def __str__(self) -> str:
        out = f"map: {self.map}\n"
        out += f"inv_map: {self.inv_map}\n"
        return out


class RowInfo:

    def __init__(self) -> None:
        self.component = ""
        self.group = ""
        self.row_index = -1

class Matrix:
    def __init__(self, size) -> None:
        self.size = size
        self.matrix : List[List[int]] = [[0]*self.size]*self.size

    def __getitem__(self, row, column):
        return self.matrix[row][column]
    
    def __setitem__(self, row, column, value):
        self.matrix[row][column] = value

    def transpose(self):
        """return a transposed version"""
        new_matrix = Matrix(self.size)
        for row in range(self.size):
            for column in range(self.size):
                new_matrix[row][column] = self.matrix[column][row]
        return new_matrix

class DSM:
    def __init__(self, filename) -> None:
        self.filename = filename

        self.header, self.orignal_data = self.load_csv(self.filename)

        self.name_map = self.parse_header(self.header)
        self.size = self.name_map.get_length()
        self.matrix = self.parse_data(self.orignal_data)

        self.groups : Dict[str, int] = self.get_groups()

        self.order = []

    def get_groups(self) -> Dict[str, int]:
        index = -1
        groups = {}

        for key, value in self.name_map.map.items():
            key: str
            component = key.split(".")[0]
            if component not in groups:
                index += 1
            groups[component] = index
        return groups

    def get_group_indexs(self):
        return list(self.groups.values())

    def set_order(self, order):
        self.order = order

    @staticmethod
    def load_csv(filename):
        with open(filename) as f:
            c = csv.reader(f, delimiter=";")
            header = c.__next__()[1:]

            data = []
            for row in c:
                data.append(row[1:])

            return header, data

    @staticmethod
    def parse_header(header):
        namemap = DoubleMap()
        [namemap.add(j, i) for i, j in enumerate(header)]
        print(namemap)
        return namemap

    @staticmethod
    def parse_data(data):
        matrix = []
        for row in data:
            row_list = []
            for value in row:
                row_list.append(int(value))
            matrix.append(row_list)

        assert len(matrix) == len(matrix[0])
        return matrix


    def get_from_order(self, new_order):
        pass


    def __str__(self) -> str:
        out = ""
        for index, row in enumerate(self.matrix):
            out += f"Row[{index}] {self.name_map.get_key(index)} : {row}\n"
        return out


def main():
    filename = "./test/graph_analysis/resources/raw_dsm.txt"
    dsm = DSM(filename)

    print(dsm.get_group_indexs())
    print(dsm.get_groups())

    # print(dsm)


if __name__ == "__main__":
    main()
