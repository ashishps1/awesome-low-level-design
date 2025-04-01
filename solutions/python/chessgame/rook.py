from piece import Piece

class Rook(Piece):
    def can_move(self, board, dest_row, dest_col):
        return self.row == dest_row or self.col == dest_col