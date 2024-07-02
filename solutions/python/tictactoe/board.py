class Board:
    def __init__(self):
        self.grid = [['-' for _ in range(3)] for _ in range(3)]
        self.moves_count = 0

    def make_move(self, row, col, symbol):
        if not (0 <= row < 3 and 0 <= col < 3) or self.grid[row][col] != '-':
            raise ValueError("Invalid move!")
        self.grid[row][col] = symbol
        self.moves_count += 1

    def is_full(self):
        return self.moves_count == 9

    def has_winner(self):
        # Check rows
        for row in range(3):
            if self.grid[row][0] != '-' and self.grid[row][0] == self.grid[row][1] == self.grid[row][2]:
                return True

        # Check columns
        for col in range(3):
            if self.grid[0][col] != '-' and self.grid[0][col] == self.grid[1][col] == self.grid[2][col]:
                return True

        # Check diagonals
        if self.grid[0][0] != '-' and self.grid[0][0] == self.grid[1][1] == self.grid[2][2]:
            return True
        return self.grid[0][2] != '-' and self.grid[0][2] == self.grid[1][1] == self.grid[2][0]

    def print_board(self):
        for row in range(3):
            print(" ".join(self.grid[row]))
        print()