using System;
using System.Collections.Generic;

public class TicTacToeDemo
{
    public static void Main()
    {
        TicTacToeSystem system = TicTacToeSystem.GetInstance();

        Player alice = new Player("Alice", Symbol.X);
        Player bob = new Player("Bob", Symbol.O);

        // --- GAME 1: Alice wins ---
        Console.WriteLine("--- GAME 1: Alice (X) vs. Bob (O) ---");
        system.CreateGame(alice, bob);
        system.PrintBoard();

        system.MakeMove(alice, 0, 0);
        system.MakeMove(bob, 1, 0);
        system.MakeMove(alice, 0, 1);
        system.MakeMove(bob, 1, 1);
        system.MakeMove(alice, 0, 2); // Alice wins, scoreboard is notified
        Console.WriteLine("----------------------------------------\n");

        // --- GAME 2: Bob wins ---
        Console.WriteLine("--- GAME 2: Alice (X) vs. Bob (O) ---");
        system.CreateGame(alice, bob); // A new game instance
        system.PrintBoard();

        system.MakeMove(alice, 0, 0);
        system.MakeMove(bob, 1, 0);
        system.MakeMove(alice, 0, 1);
        system.MakeMove(bob, 1, 1);
        system.MakeMove(alice, 2, 2);
        system.MakeMove(bob, 1, 2); // Bob wins, scoreboard is notified
        Console.WriteLine("----------------------------------------\n");

        // --- GAME 3: A Draw ---
        Console.WriteLine("--- GAME 3: Alice (X) vs. Bob (O) - Draw ---");
        system.CreateGame(alice, bob);
        system.PrintBoard();

        system.MakeMove(alice, 0, 0);
        system.MakeMove(bob, 0, 1);
        system.MakeMove(alice, 0, 2);
        system.MakeMove(bob, 1, 1);
        system.MakeMove(alice, 1, 0);
        system.MakeMove(bob, 1, 2);
        system.MakeMove(alice, 2, 1);
        system.MakeMove(bob, 2, 0);
        system.MakeMove(alice, 2, 2); // Draw, scoreboard is not notified of a winner
        Console.WriteLine("----------------------------------------\n");

        // --- Final Scoreboard ---
        // We get the scoreboard from the system and print its final state
        system.PrintScoreBoard();
    }
}