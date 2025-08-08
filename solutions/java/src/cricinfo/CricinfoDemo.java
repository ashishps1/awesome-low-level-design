package cricinfo;

import cricinfo.enums.PlayerRole;
import cricinfo.enums.WicketType;
import cricinfo.entity.*;
import cricinfo.observer.CommentaryDisplay;
import cricinfo.observer.ScorecardDisplay;
import cricinfo.observer.UserNotifier;
import cricinfo.strategy.T20FormatStrategy;

import java.util.List;

public class CricinfoDemo {
    public static void main(String[] args) {
        // Get the Singleton service instance
        CricInfoService service = CricInfoService.getInstance();

        // 1. Setup Players and Teams
        Player p1 = service.addPlayer("P1", "Virat", PlayerRole.BATSMAN);
        Player p2 = service.addPlayer("P2", "Rohit", PlayerRole.BATSMAN);
        Player p3 = service.addPlayer("P3", "Bumrah", PlayerRole.BOWLER);
        Player p4 = service.addPlayer("P4", "Jadeja", PlayerRole.ALL_ROUNDER);

        Player p5 = service.addPlayer("P5", "Warner", PlayerRole.BATSMAN);
        Player p6 = service.addPlayer("P6", "Smith", PlayerRole.BATSMAN);
        Player p7 = service.addPlayer("P7", "Starc", PlayerRole.BOWLER);
        Player p8 = service.addPlayer("P8", "Maxwell", PlayerRole.ALL_ROUNDER);

        Team india = new Team("T1", "India", List.of(p1, p2, p3, p4));
        Team australia = new Team("T2", "Australia", List.of(p5, p6, p7, p8));

        // 2. Create a T20 Match using the service
        Match t20Match = service.createMatch(india, australia, new T20FormatStrategy());
        String matchId = t20Match.getId();

        // 3. Create and subscribe observers
        ScorecardDisplay scorecard = new ScorecardDisplay();
        CommentaryDisplay commentary = new CommentaryDisplay();
        UserNotifier notifier = new UserNotifier();

        service.subscribeToMatch(matchId, scorecard);
        service.subscribeToMatch(matchId, commentary);
        service.subscribeToMatch(matchId, notifier);

        // 4. Start the match
        service.startMatch(matchId);

        System.out.println("\n--- SIMULATING FIRST INNINGS ---");
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p1).withRuns(2).build());
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p1).withRuns(1).build());
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p2).withRuns(6).build());

        Wicket p2Wicket = new Wicket.Builder(WicketType.BOWLED, p2).build();
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p2).withRuns(0).withWicket(p2Wicket).build());

        Wicket p3Wicket = new Wicket.Builder(WicketType.LBW, p3).build();
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p3).withRuns(0).withWicket(p3Wicket).build());

        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p4).withRuns(4).build());

        Wicket p4Wicket = new Wicket.Builder(WicketType.CAUGHT, p4).caughtBy(p6).build();
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p7).facedBy(p4).withRuns(0).withWicket(p4Wicket).build());

        // The system is now in an IN_BREAK state
        System.out.println("\n\n--- INNINGS BREAK ---");
        System.out.println("Players are off the field. Preparing for the second innings.");

        // 2. Start the second innings
        service.startNextInnings(matchId);

        System.out.println("\n--- SIMULATING SECOND INNINGS ---");
        // Simulate a few balls of the second innings to show it works
        // Now Australia is batting (p5, p6) and India is bowling (p3)
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p3).facedBy(p5).withRuns(4).build());

        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p3).facedBy(p5).withRuns(1).build());

        Wicket p5Wicket = new Wicket.Builder(WicketType.BOWLED, p5).build();
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p3).facedBy(p5).withRuns(0).withWicket(p5Wicket).build());

        Wicket p7Wicket = new Wicket.Builder(WicketType.LBW, p7).build();
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p3).facedBy(p7).withRuns(0).withWicket(p7Wicket).build());

        Wicket p8Wicket = new Wicket.Builder(WicketType.STUMPED, p8).build();
        service.processBallUpdate(matchId, new Ball.BallBuilder()
                .bowledBy(p3).facedBy(p8).withRuns(0).withWicket(p8Wicket).build());

        service.endMatch(matchId);
    }
}
