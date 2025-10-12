from tictactoesystem import TicTacToeSystem
from player import Player
from symbol import Symbol

class TicTacToeDemo:
    @staticmethod
    def main():
        system = TicTacToeSystem.get_instance()
        
        alice = Player("Alice", Symbol.X)
        bob = Player("Bob", Symbol.O)
        
        # --- GAME 1: Alice wins ---
        print("--- GAME 1: Alice (X) vs. Bob (O) ---")
        system.create_game(alice, bob)
        system.print_board()
        
        system.make_move(alice, 0, 0)
        system.make_move(bob, 1, 0)
        system.make_move(alice, 0, 1)
        system.make_move(bob, 1, 1)
        system.make_move(alice, 0, 2)  # Alice wins, scoreboard is notified
        print("----------------------------------------\n")
        
        # --- GAME 2: Bob wins ---
        print("--- GAME 2: Alice (X) vs. Bob (O) ---")
        system.create_game(alice, bob)  # A new game instance
        system.print_board()
        
        system.make_move(alice, 0, 0)
        system.make_move(bob, 1, 0)
        system.make_move(alice, 0, 1)
        system.make_move(bob, 1, 1)
        system.make_move(alice, 2, 2)
        system.make_move(bob, 1, 2)  # Bob wins, scoreboard is notified
        print("----------------------------------------\n")
        
        # --- GAME 3: A Draw ---
        print("--- GAME 3: Alice (X) vs. Bob (O) - Draw ---")
        system.create_game(alice, bob)
        system.print_board()
        
        system.make_move(alice, 0, 0)
        system.make_move(bob, 0, 1)
        system.make_move(alice, 0, 2)
        system.make_move(bob, 1, 1)
        system.make_move(alice, 1, 0)
        system.make_move(bob, 1, 2)
        system.make_move(alice, 2, 1)
        system.make_move(bob, 2, 0)
        system.make_move(alice, 2, 2)  # Draw, scoreboard is not notified of a winner
        print("----------------------------------------\n")
        
        # --- Final Scoreboard ---
        # We get the scoreboard from the system and print its final state
        system.print_score_board()


if __name__ == "__main__":
    TicTacToeDemo.main()