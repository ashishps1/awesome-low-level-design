using System;
using System.Collections.Generic;
using System.Linq;

public class CricinfoDemo
{
    public static void Main()
    {
        var service = CricInfoService.GetInstance();

        // Setup Players and Teams
        var p1 = service.AddPlayer("P1", "Virat", PlayerRole.BATSMAN);
        var p2 = service.AddPlayer("P2", "Rohit", PlayerRole.BATSMAN);
        var p3 = service.AddPlayer("P3", "Bumrah", PlayerRole.BOWLER);
        var p4 = service.AddPlayer("P4", "Jadeja", PlayerRole.ALL_ROUNDER);

        var p5 = service.AddPlayer("P5", "Warner", PlayerRole.BATSMAN);
        var p6 = service.AddPlayer("P6", "Smith", PlayerRole.BATSMAN);
        var p7 = service.AddPlayer("P7", "Starc", PlayerRole.BOWLER);
        var p8 = service.AddPlayer("P8", "Maxwell", PlayerRole.ALL_ROUNDER);

        var india = new Team("T1", "India", new List<Player> { p1, p2, p3, p4 });
        var australia = new Team("T2", "Australia", new List<Player> { p5, p6, p7, p8 });

        // Create a T20 Match
        var t20Match = service.CreateMatch(india, australia, new T20FormatStrategy());
        string matchId = t20Match.GetId();

        // Create and subscribe observers
        var scorecard = new ScorecardDisplay();
        var commentary = new CommentaryDisplay();
        var notifier = new UserNotifier();

        service.SubscribeToMatch(matchId, scorecard);
        service.SubscribeToMatch(matchId, commentary);
        service.SubscribeToMatch(matchId, notifier);

        // Start the match
        service.StartMatch(matchId);

        Console.WriteLine("\n--- SIMULATING FIRST INNINGS ---");
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p7).WithFacedBy(p2).WithRuns(6).Build());

        var p2Wicket = new WicketBuilder(WicketType.BOWLED, p2).Build();
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p7).WithFacedBy(p2).WithRuns(0).WithWicket(p2Wicket).Build());

        var p3Wicket = new WicketBuilder(WicketType.LBW, p3).Build();
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p7).WithFacedBy(p3).WithRuns(0).WithWicket(p3Wicket).Build());

        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p7).WithFacedBy(p4).WithRuns(4).Build());

        var p4Wicket = new WicketBuilder(WicketType.CAUGHT, p4).WithCaughtBy(p6).Build();
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p7).WithFacedBy(p4).WithRuns(0).WithWicket(p4Wicket).Build());

        Console.WriteLine("\n\n--- INNINGS BREAK ---");
        Console.WriteLine("Players are off the field. Preparing for the second innings.");

        // Start the second innings
        service.StartNextInnings(matchId);

        Console.WriteLine("\n--- SIMULATING SECOND INNINGS ---");
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p3).WithFacedBy(p5).WithRuns(4).Build());

        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p3).WithFacedBy(p5).WithRuns(1).Build());

        var p5Wicket = new WicketBuilder(WicketType.BOWLED, p5).Build();
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p3).WithFacedBy(p5).WithRuns(0).WithWicket(p5Wicket).Build());

        var p7Wicket = new WicketBuilder(WicketType.LBW, p7).Build();
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p3).WithFacedBy(p7).WithRuns(0).WithWicket(p7Wicket).Build());

        var p8Wicket = new WicketBuilder(WicketType.STUMPED, p8).Build();
        service.ProcessBallUpdate(matchId, new BallBuilder()
                                   .WithBowledBy(p3).WithFacedBy(p8).WithRuns(0).WithWicket(p8Wicket).Build());

        service.EndMatch(matchId);
    }
}