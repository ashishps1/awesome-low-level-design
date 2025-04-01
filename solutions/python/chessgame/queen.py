from piece import Piece

class Queen(Piece):
    def can_move(self, board, dest_row, dest_col):
        row_diff = abs(dest_row - self.row)
        col_diff = abs(dest_col - self.col)
        return (row_diff == col_diff) or (self.row == dest_row or self.col == dest_col)