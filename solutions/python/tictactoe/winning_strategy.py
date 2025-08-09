from abc import ABC, abstractmethod
from board import Board
from player import Player

class WinningStrategy(ABC):
    @abstractmethod
    def check_winner(self, board: Board, player: Player) -> bool:
        pass

class RowWinningStrategy(WinningStrategy):
    def check_winner(self, board: Board, player: Player) -> bool:
        for row in range(board.get_size()):
            row_win = True
            for col in range(board.get_size()):
                if board.get_cell(row, col).get_symbol() != player.get_symbol():
                    row_win = False
                    break
            if row_win:
                return True
        return False

class ColumnWinningStrategy(WinningStrategy):
    def check_winner(self, board: Board, player: Player) -> bool:
        for col in range(board.get_size()):
            col_win = True
            for row in range(board.get_size()):
                if board.get_cell(row, col).get_symbol() != player.get_symbol():
                    col_win = False
                    break
            if col_win:
                return True
        return False

class DiagonalWinningStrategy(WinningStrategy):
    def check_winner(self, board: Board, player: Player) -> bool:
        # Main diagonal
        main_diag_win = True
        for i in range(board.get_size()):
            if board.get_cell(i, i).get_symbol() != player.get_symbol():
                main_diag_win = False
                break
        if main_diag_win:
            return True
        
        # Anti-diagonal
        anti_diag_win = True
        for i in range(board.get_size()):
            if board.get_cell(i, board.get_size() - 1 - i).get_symbol() != player.get_symbol():
                anti_diag_win = False
                break
        return anti_diag_win