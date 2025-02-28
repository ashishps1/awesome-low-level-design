using System;
using System.Collections.Generic;

namespace Cricinfo
{
    public class CricinfoDemo
    {
        public static void Run()
        {
            // Create teams
            List<Player> team1Players = new List<Player>
            {
                new Player("P101", "Player 1", "Batsman"),
                new Player("P102", "Player 2", "Bowler"),
                new Player("P103", "Player 3", "All-rounder")
            };

            List<Player> team2Players = new List<Player>
            {
                new Player("P201", "Player 4", "Batsman"),
                new Player("P202", "Player 5", "Bowler"),
                new Player("P203", "Player 6", "All-rounder")
            };

            Team team1 = new Team("T1", "Team 1", team1Players);
            Team team2 = new Team("T2", "Team 2", team2Players);
            List<Team> teams = new List<Team> { team1, team2 };

            // Create a match
            Match match = new Match("M001", "Match 1", "Venue 1", DateTime.Now, teams);

            // Create Cricinfo system
            CricinfoSystem cricinfoSystem = new CricinfoSystem();

            // Add the match to the system
            cricinfoSystem.AddMatch(match);

            // Create a scorecard for the match
            cricinfoSystem.CreateScorecard(match);

            // Get the scorecard
            string scorecardId = "SC-M001-0001";
            Scorecard scorecard = cricinfoSystem.GetScorecard(scorecardId);

            // Update scores
            cricinfoSystem.UpdateScore(scorecardId, "T1", 100);
            cricinfoSystem.UpdateScore(scorecardId, "T2", 75);

            // Create innings
            Innings innings1 = new Innings("I1", "T1", "T2");
            Innings innings2 = new Innings("I2", "T2", "T1");

            // Add overs to innings
            Over over1 = new Over(1);
            over1.AddBall(new Ball(1, "P202", "P101", "4"));
            over1.AddBall(new Ball(2, "P202", "P101", "6"));
            innings1.AddOver(over1);

            Over over2 = new Over(2);
            over2.AddBall(new Ball(1, "P102", "P201", "1"));
            over2.AddBall(new Ball(2, "P102", "P201", "0"));
            innings1.AddOver(over2);

            // Add innings to the scorecard
            cricinfoSystem.AddInnings(scorecardId, innings1);
            cricinfoSystem.AddInnings(scorecardId, innings2);

            // Display the scorecard
            Console.WriteLine("Scorecard ID: " + scorecard.GetId());
            Console.WriteLine("Match: " + scorecard.GetMatch().GetTitle());
            Console.WriteLine("Team Scores:");
            foreach (var entry in scorecard.GetTeamScores())
            {
                Console.WriteLine(entry.Key + ": " + entry.Value);
            }

            Console.WriteLine("Innings:");
            foreach (Innings innings in scorecard.GetInnings())
            {
                Console.WriteLine("Innings ID: " + innings.GetId());
                Console.WriteLine("Batting Team: " + innings.GetBattingTeamId());
                Console.WriteLine("Bowling Team: " + innings.GetBowlingTeamId());
                Console.WriteLine("Overs:");
                foreach (Over over in innings.GetOvers())
                {
                    Console.WriteLine("Over " + over.GetOverNumber());
                    foreach (Ball ball in over.GetBalls())
                    {
                        Console.WriteLine("Ball " + ball.GetBallNumber() + ": " +
                                          ball.GetBowler() + " to " + ball.GetBatsman() + " - " + ball.GetResult());
                    }
                }
                Console.WriteLine();
            }
        }
    }
}