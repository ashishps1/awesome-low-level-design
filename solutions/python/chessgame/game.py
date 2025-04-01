from board import Board
from player import Player
from color import Color
from move import Move

class Game:
    def __init__(self):
        self.board = Board()
        self.players = [Player(Color.WHITE), Player(Color.BLACK)]
        self.current_player = 0

    def start(self):
        # Game loop
        while not self._is_game_over():
            player = self.players[self.current_player]
            print(f"{player.color.name}'s turn.")

            # Get move from the player
            move = self._get_player_move(player)

            # Make the move on the board
            player.make_move(self.board, move)

            # Switch to the next player
            self.current_player = (self.current_player + 1) % 2

        # Display game result
        self._display_result()

    def _is_game_over(self):
        return self.board.is_checkmate(Color.WHITE) or self.board.is_checkmate(Color.BLACK) or \
               self.board.is_stalemate(Color.WHITE) or self.board.is_stalemate(Color.BLACK)

    def _get_player_move(self, player):
        # TODO: Implement logic to get a valid move from the player
        # For simplicity, let's assume the player enters the move via console input
        source_row = int(input("Enter source row: "))
        source_col = int(input("Enter source column: "))
        dest_row = int(input("Enter destination row: "))
        dest_col = int(input("Enter destination column: "))

        piece = self.board.get_piece(source_row, source_col)
        if piece is None or piece.color != player.color:
            raise ValueError("Invalid piece selection!")

        return Move(piece, dest_row, dest_col)

    def _display_result(self):
        if self.board.is_checkmate(Color.WHITE):
            print("Black wins by checkmate!")
        elif self.board.is_checkmate(Color.BLACK):
            print("White wins by checkmate!")
        elif self.board.is_stalemate(Color.WHITE) or self.board.is_stalemate(Color.BLACK):
            print("The game ends in a stalemate!")