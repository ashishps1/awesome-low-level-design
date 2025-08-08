package cricinfo.observer;

import cricinfo.enums.MatchStatus;
import cricinfo.entity.Innings;
import cricinfo.entity.Match;
import cricinfo.entity.Ball;

public class ScorecardDisplay implements MatchObserver {
    @Override
    public void update(Match match, Ball lastBall) {
        // This block handles end-of-innings or end-of-match signals
        if (match.getCurrentStatus() == MatchStatus.FINISHED) {
            System.out.println("\n--- MATCH RESULT ---");
            System.out.println(match.getResultMessage().toUpperCase());
            System.out.println("--------------------");

            System.out.println("Player Stats:");
            int counter = 1;
            for (Innings inning: match.getInnings()) {
                System.out.println("Inning " + counter++);
                inning.printPlayerStats();
            }

        } else if (match.getCurrentStatus() == MatchStatus.IN_BREAK) {
            System.out.println("\n--- END OF INNINGS ---");
            Innings lastInnings = match.getInnings().get(match.getInnings().size() - 1);
            System.out.printf("Final Score: %s: %d/%d (Overs: %.1f)%n",
                    lastInnings.getBattingTeam().getName(),
                    lastInnings.getScore(),
                    lastInnings.getWickets(),
                    lastInnings.getOvers());
            System.out.println("------------------------");
        } else {
            // This block runs for every ball during a live match
            System.out.println("\n--- SCORECARD UPDATE ---");
            Innings currentInnings = match.getCurrentInnings();
            System.out.printf("%s: %d/%d (Overs: %.1f)%n",
                    currentInnings.getBattingTeam().getName(),
                    currentInnings.getScore(),
                    currentInnings.getWickets(),
                    currentInnings.getOvers());
            System.out.println("------------------------");
        }
    }
}