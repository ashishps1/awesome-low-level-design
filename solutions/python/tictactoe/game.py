from game_subject import GameSubject
from game_state import InProgressState
from game_status import GameStatus
from player import Player
from board import Board
from winning_strategy import RowWinningStrategy, ColumnWinningStrategy, DiagonalWinningStrategy
from game_state import GameState

class Game(GameSubject):
    def __init__(self, player1: Player, player2: Player):
        super().__init__()
        self.board = Board(3)
        self.player1 = player1
        self.player2 = player2
        self.current_player = player1  # Player 1 starts
        self.winner = None
        self.status = GameStatus.IN_PROGRESS
        self.state = InProgressState()
        self.winning_strategies = [
            RowWinningStrategy(),
            ColumnWinningStrategy(),
            DiagonalWinningStrategy()
        ]
    
    def make_move(self, player: Player, row: int, col: int):
        self.state.handle_move(self, player, row, col)
    
    def check_winner(self, player: Player) -> bool:
        for strategy in self.winning_strategies:
            if strategy.check_winner(self.board, player):
                return True
        return False
    
    def switch_player(self):
        self.current_player = self.player2 if self.current_player == self.player1 else self.player1
    
    def get_board(self):
        return self.board
    
    def get_current_player(self):
        return self.current_player
    
    def get_winner(self):
        return self.winner
    
    def set_winner(self, winner: Player):
        self.winner = winner
    
    def get_status(self):
        return self.status
    
    def set_state(self, state: GameState):
        self.state = state
    
    def set_status(self, status: GameStatus):
        self.status = status
        # Notify observers when the status changes to a finished state
        if status != GameStatus.IN_PROGRESS:
            self.notify_observers()