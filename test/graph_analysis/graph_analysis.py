import csv


class ToFromMap:
    def __init__(self) -> None:
        self._to = {}
        self._from = {}

    def add(self, key, value):
        self._to[key] = value
        self._from[value] = key
        assert len(self._to) == len(self._from)

    def get_value(self, key):
        return self._to[key]

    def get_key(self, value):
        return self._from[value]

    def get_length(self):
        return len(self._to)

    def __str__(self) -> str:
        out = f"To: {self._to}\n"
        out += f"From: {self._from}\n"
        return out


class DSM:
    def __init__(self, filename) -> None:
        self.filename = filename

        self.header, self.orignal_data = self.load_csv(self.filename)

        self.name_map = self.parse_header(self.header)
        self.nr_items = self.name_map.get_length()
        self.matrix = self.parse_data(self.orignal_data)

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
        namemap = ToFromMap()
        [namemap.add(i, j) for i, j in enumerate(header)]
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

    def __str__(self) -> str:
        out = ""
        for index, row in enumerate(self.matrix):
            out += f"Row[{index}] {self.name_map.get_value(index)} : {row}\n"
        return out


def main():
    filename = "./test/graph_analysis/resources/raw_dsm.txt"
    dsm = DSM(filename)

    print(dsm)


if __name__ == "__main__":
    main()
