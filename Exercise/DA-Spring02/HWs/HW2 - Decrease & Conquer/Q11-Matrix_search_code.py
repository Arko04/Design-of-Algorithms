from numpy import transpose

class Dashboard:
    def __init__(self):
        print("Determine number of rows or columns of your matrix please:")
        self.n = int(input())

        print(f"Enter an {self.n}*{self.n} matrix please:")
        self.matrix = []

        for i in range(self.n):
            row = list(map(int, input().split()))
            self.matrix.append(row)
        
        print("\nPlease enter some integr to find it in your matrix:")
        self.key = int(input())

    def sort_matrix(self):
        for row in self.matrix:
            row.sort()
        self.matrix = transpose(self.matrix).tolist()
        for row in self.matrix:
            row.sort()
        self.matrix = transpose(self.matrix).tolist()
        
        print('\nWe first sort the matrix to find key in O(n). Sorted matrix is:')
        for row in self.matrix :
            print(*row)
    
    def find_key(self):
        i, j = 0, self.n - 1
        while (i < self.n and j > -1):
            if self.matrix[i][j] == self.key:
                return i, j
            else:
                if self.matrix[i][j] > self.key:
                    j -= 1
                else:
                    i += 1
        return -1
    
    def start(self):
        self.sort_matrix()
        ans = self.find_key()
        if ans == -1:
            print(f"'{self.key}' doesn't exist in your matrix")
        else:
            print(f"\n'{self.key}' found in location ({ans[0] + 1}, {ans[1] + 1}) in sorted matrix")

d = Dashboard()
d.start()
