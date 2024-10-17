
import csv



def load_csv(filename):

    with open(filename) as f:
        c = csv.reader(f, delimiter=";")
        row_index = 0
        row_name_map = {}
        top_row = c.__next__()

        name_map = {i:j for i, j }

        return
        for row in c:
        
            row_name_map[row[0]] = row_index
            row_index += 1


            print(row)
    


def main():

    filename = './test/graph_analysis/resources/raw_dsm.txt'
    data = load_csv(filename)

    print(data)

if __name__ == "__main__":
    main()


