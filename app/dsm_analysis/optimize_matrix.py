import itertools
from matrix import Matrix

class OptimizeMatrix:

    def __init__(self, matrix) -> None:
        
        self.matrix : Matrix = matrix

    def optimize(self):
        initial = list(range(self.matrix.size))
        print(initial)

        combinations = list(itertools.permutations(initial, len(initial)))

        print(combinations)

        lowest_rating = 10**10
        best_combo = []

        print(self.matrix)

        for combo in combinations:
            print("------------")
            m = self.matrix.set_order(combo)
            rating = m.get_rating()
            if rating < lowest_rating:
                lowest_rating = rating
                best_combo = combo 
                print(f"{best_combo=} {rating=}")
                print(m)
        return best_combo

def tests():
    
    m = Matrix(3)
    m[[1, 1]] = 1
    m[[0, 1]] = 1

    OptimizeMatrix(m).optimize()


if __name__ == "__main__":
    tests()
