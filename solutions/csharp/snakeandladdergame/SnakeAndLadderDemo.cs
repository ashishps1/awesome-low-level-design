using System;
using System.Collections.Generic;

namespace SnakeAndLadderGame
{
    public class SnakeAndLadderDemo
    {
        public static void Run()
        {
            GameManager gameManager = GameManager.GetInstance();

            // Start game 1
            List<string> players1 = new List<string> { "Player 1", "Player 2", "Player 3" };
            gameManager.StartNewGame(players1);

            // Start game 2
            List<string> players2 = new List<string> { "Player 4", "Player 5" };
            gameManager.StartNewGame(players2);
        }
    }
}