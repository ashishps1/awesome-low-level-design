from game_status import GameStatus
from player import Player
from board import Board
from dice import Dice
from snake import Snake
from ladder import Ladder
from typing import List
from collections import deque
from board_entity import BoardEntity

class Game:
    class Builder:
        def __init__(self):
            self.board = None
            self.players = None
            self.dice = None
        
        def set_board(self, board_size: int, board_entities: List[BoardEntity]):
            self.board = Board(board_size, board_entities)
            return self
        
        def set_players(self, player_names: List[str]):
            self.players = deque()
            for player_name in player_names:
                self.players.append(Player(player_name))
            return self
        
        def set_dice(self, dice: Dice):
            self.dice = dice
            return self
        
        def build(self):
            if self.board is None or self.players is None or self.dice is None:
                raise ValueError("Board, Players, and Dice must be set.")
            return Game(self)
    
    def __init__(self, builder: 'Game.Builder'):
        self.board = builder.board
        self.players = deque(builder.players)
        self.dice = builder.dice
        self.status = GameStatus.NOT_STARTED
        self.winner = None
    
    def play(self):
        if len(self.players) < 2:
            print("Cannot start game. At least 2 players are required.")
            return
        
        self.status = GameStatus.RUNNING
        print("Game started!")
        
        while self.status == GameStatus.RUNNING:
            current_player = self.players.popleft()
            self.take_turn(current_player)
            
            # If the game is not finished and the player didn't roll a 6, add them back to the queue
            if self.status == GameStatus.RUNNING:
                self.players.append(current_player)
        
        print("Game Finished!")
        if self.winner is not None:
            print(f"The winner is {self.winner.get_name()}!")
    
    def take_turn(self, player: Player):
        roll = self.dice.roll()
        print(f"\n{player.get_name()}'s turn. Rolled a {roll}.")
        
        current_position = player.get_position()
        next_position = current_position + roll
        
        if next_position > self.board.get_size():
            print(f"Oops, {player.get_name()} needs to land exactly on {self.board.get_size()}. Turn skipped.")
            return
        
        if next_position == self.board.get_size():
            player.set_position(next_position)
            self.winner = player
            self.status = GameStatus.FINISHED
            print(f"Hooray! {player.get_name()} reached the final square {self.board.get_size()} and won!")
            return
        
        final_position = self.board.get_final_position(next_position)
        
        if final_position > next_position:  # Ladder
            print(f"Wow! {player.get_name()} found a ladder 🪜 at {next_position} and climbed to {final_position}.")
        elif final_position < next_position:  # Snake
            print(f"Oh no! {player.get_name()} was bitten by a snake 🐍 at {next_position} and slid down to {final_position}.")
        else:
            print(f"{player.get_name()} moved from {current_position} to {final_position}.")
        
        player.set_position(final_position)
        
        if roll == 6:
            print(f"{player.get_name()} rolled a 6 and gets another turn!")
            self.take_turn(player)