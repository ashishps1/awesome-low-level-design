from abc import ABC, abstractmethod
from player import Player
from invalid_move_exception import InvalidMoveException
from game_status import GameStatus
from symbol import Symbol

class GameState(ABC):
    @abstractmethod
    def handle_move(self, game, player: Player, row: int, col: int):
        pass

class InProgressState(GameState):
    def handle_move(self, game, player: Player, row: int, col: int):
        if game.get_current_player() != player:
            raise InvalidMoveException("Not your turn!")
        
        # Place the piece on the board
        game.get_board().place_symbol(row, col, player.get_symbol())
        
        # Check for a winner or a draw
        if game.check_winner(player):
            game.set_winner(player)
            game.set_status(GameStatus.WINNER_X if player.get_symbol() == Symbol.X else GameStatus.WINNER_O)
            game.set_state(WinnerState())
        elif game.get_board().is_full():
            game.set_status(GameStatus.DRAW)
            game.set_state(DrawState())
        else:
            # If the game is still in progress, switch players
            game.switch_player()


class DrawState(GameState):
    def handle_move(self, game, player: Player, row: int, col: int):
        raise InvalidMoveException("Game is already over. It was a draw.")


class WinnerState(GameState):
    def handle_move(self, game, player: Player, row: int, col: int):
        raise InvalidMoveException(f"Game is already over. {game.get_winner().get_name()} has won.")