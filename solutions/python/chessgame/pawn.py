from piece import Piece
from color import Color

class Pawn(Piece):
    def can_move(self, board, dest_row, dest_col):
        row_diff = dest_row - self.row
        col_diff = abs(dest_col - self.col)

        if self.color == Color.WHITE:
            return (row_diff == 1 and col_diff == 0) or \
                   (self.row == 1 and row_diff == 2 and col_diff == 0) or \
                   (row_diff == 1 and col_diff == 1 and board.get_piece(dest_row, dest_col) is not None)
        else:
            return (row_diff == -1 and col_diff == 0) or \
                   (self.row == 6 and row_diff == -2 and col_diff == 0) or \
                   (row_diff == -1 and col_diff == 1 and board.get_piece(dest_row, dest_col) is not None)