from game_observer import GameObserver

class Scoreboard(GameObserver):
    def __init__(self):
        self.scores = {}
    
    def update(self, game):
        # The scoreboard only cares about finished games with a winner
        if game.get_winner() is not None:
            winner_name = game.get_winner().get_name()
            self.scores[winner_name] = self.scores.get(winner_name, 0) + 1
            print(f"[Scoreboard] {winner_name} wins! Their new score is {self.scores[winner_name]}.")
    
    def print_scores(self):
        print("\n--- Overall Scoreboard ---")
        if not self.scores:
            print("No games with a winner have been played yet.")
            return
        
        for player_name, score in self.scores.items():
            print(f"Player: {player_name:<10} | Wins: {score}")
        print("--------------------------\n")