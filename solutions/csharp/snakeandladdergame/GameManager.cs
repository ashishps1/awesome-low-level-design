using System;
using System.Collections.Generic;
using System.Threading;

namespace SnakeAndLadderGame
{
    public class GameManager
    {
        private static GameManager _instance;
        private readonly List<SnakeAndLadderGame> _games;

        private GameManager()
        {
            _games = new List<SnakeAndLadderGame>();
        }

        public static GameManager GetInstance()
        {
            if (_instance == null)
            {
                _instance = new GameManager();
            }
            return _instance;
        }

        public void StartNewGame(List<string> playerNames)
        {
            SnakeAndLadderGame game = new SnakeAndLadderGame(playerNames);
            _games.Add(game);
            Thread gameThread = new Thread(new ThreadStart(game.Play));
            gameThread.Start();
        }
    }
}