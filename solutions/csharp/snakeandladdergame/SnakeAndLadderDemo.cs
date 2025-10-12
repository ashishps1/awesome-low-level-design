using System;
using System.Collections.Generic;

public class SnakeAndLadderDemo
{
    public static void Main()
    {
        List<BoardEntity> boardEntities = new List<BoardEntity>
        {
            new Snake(17, 7), new Snake(54, 34),
            new Snake(62, 19), new Snake(98, 79),
            new Ladder(3, 38), new Ladder(24, 33),
            new Ladder(42, 93), new Ladder(72, 84)
        };

        List<string> players = new List<string> { "Alice", "Bob", "Charlie" };

        Game game = new GameBuilder()
            .SetBoard(100, boardEntities)
            .SetPlayers(players)
            .SetDice(new Dice(1, 6))
            .Build();            

        game.Play();
    }
}