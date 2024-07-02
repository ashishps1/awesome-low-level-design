from game_manager import GameManager

class SnakeAndLadderDemo:
    def run():
        game_manager = GameManager.get_instance()

        # Start game 1
        players1 = ["Player 1", "Player 2", "Player 3"]
        game_manager.start_new_game(players1)

        # Start game 2
        players2 = ["Player 4", "Player 5"]
        game_manager.start_new_game(players2)

if __name__ == "__main__":
    SnakeAndLadderDemo.run()