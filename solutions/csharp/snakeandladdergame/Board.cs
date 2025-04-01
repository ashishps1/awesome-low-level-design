using System;
using System.Collections.Generic;

namespace SnakeAndLadderGame
{
    public class Board
    {
        private const int BoardSize = 100;
        private readonly List<Snake> _snakes;
        private readonly List<Ladder> _ladders;

        public Board()
        {
            _snakes = new List<Snake>();
            _ladders = new List<Ladder>();
            InitializeSnakesAndLadders();
        }

        private void InitializeSnakesAndLadders()
        {
            // Initialize snakes
            _snakes.Add(new Snake(16, 6));
            _snakes.Add(new Snake(48, 26));
            _snakes.Add(new Snake(64, 60));
            _snakes.Add(new Snake(93, 73));

            // Initialize ladders
            _ladders.Add(new Ladder(1, 38));
            _ladders.Add(new Ladder(4, 14));
            _ladders.Add(new Ladder(9, 31));
            _ladders.Add(new Ladder(21, 42));
            _ladders.Add(new Ladder(28, 84));
            _ladders.Add(new Ladder(51, 67));
            _ladders.Add(new Ladder(80, 99));
        }

        public int GetBoardSize()
        {
            return BoardSize;
        }

        public int GetNewPositionAfterSnakeOrLadder(int position)
        {
            foreach (var snake in _snakes)
            {
                if (snake.Start == position)
                {
                    return snake.End;
                }
            }

            foreach (var ladder in _ladders)
            {
                if (ladder.Start == position)
                {
                    return ladder.End;
                }
            }

            return position;
        }
    }
}