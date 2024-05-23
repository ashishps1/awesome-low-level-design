package cricinfo;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

public class CricinfoDemo {
    public static void run() {
        // Create teams
        List<Player> team1Players = Arrays.asList(
                new Player("P101", "Player 1", "Batsman"),
                new Player("P102", "Player 2", "Bowler"),
                new Player("P103", "Player 3", "All-rounder")
        );
        List<Player> team2Players = Arrays.asList(
                new Player("P201", "Player 4", "Batsman"),
                new Player("P202", "Player 5", "Bowler"),
                new Player("P203", "Player 6", "All-rounder")
        );
        Team team1 = new Team("T1", "Team 1", team1Players);
        Team team2 = new Team("T2", "Team 2", team2Players);
        List<Team> teams = Arrays.asList(team1, team2);

        // Create a match
        Match match = new Match("M001", "Match 1", "Venue 1", LocalDateTime.now(), teams);

        // Create Cricinfo system
        CricinfoSystem cricinfoSystem = new CricinfoSystem();

        // Add the match to the system
        cricinfoSystem.addMatch(match);

        // Create a scorecard for the match
        cricinfoSystem.createScorecard(match);

        // Get the scorecard
        String scorecardId = "SC-M001-0001";
        Scorecard scorecard = cricinfoSystem.getScorecard(scorecardId);

        // Update scores
        cricinfoSystem.updateScore(scorecardId, "T1", 100);
        cricinfoSystem.updateScore(scorecardId, "T2", 75);

        // Create innings
        Innings innings1 = new Innings("I1", "T1", "T2");
        Innings innings2 = new Innings("I2", "T2", "T1");

        // Add overs to innings
        Over over1 = new Over(1);
        over1.addBall(new Ball(1, "P202", "P101", "4"));
        over1.addBall(new Ball(2, "P202", "P101", "6"));
        innings1.addOver(over1);

        Over over2 = new Over(2);
        over2.addBall(new Ball(1, "P102", "P201", "1"));
        over2.addBall(new Ball(2, "P102", "P201", "0"));
        innings1.addOver(over2);

        // Add innings to the scorecard
        cricinfoSystem.addInnings(scorecardId, innings1);
        cricinfoSystem.addInnings(scorecardId, innings2);

        // Get the updated scorecard
        Scorecard updatedScorecard = cricinfoSystem.getScorecard(scorecardId);

        // Display the scorecard
        System.out.println("Scorecard ID: " + updatedScorecard.getId());
        System.out.println("Match: " + updatedScorecard.getMatch().getTitle());
        System.out.println("Team Scores:");
        for (Map.Entry<String, Integer> entry : updatedScorecard.getTeamScores().entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
        System.out.println("Innings:");
        for (Innings innings : updatedScorecard.getInnings()) {
            System.out.println("Innings ID: " + innings.getId());
            System.out.println("Batting Team: " + innings.getBattingTeamId());
            System.out.println("Bowling Team: " + innings.getBowlingTeamId());
            System.out.println("Overs:");
            for (Over over : innings.getOvers()) {
                System.out.println("Over " + over.getOverNumber());
                for (Ball ball : over.getBalls()) {
                    System.out.println("Ball " + ball.getBallNumber() + ": " +
                            ball.getBowler() + " to " + ball.getBatsman() + " - " + ball.getResult());
                }
            }
            System.out.println();
        }
    }
}
