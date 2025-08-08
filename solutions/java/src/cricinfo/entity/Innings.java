package cricinfo.entity;

import cricinfo.enums.ExtraType;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class Innings {
    private final Team battingTeam;
    private final Team bowlingTeam;
    private int score;
    private int wickets;
    private final List<Ball> balls;
    private final Map<Player, PlayerStats> playerStats;

    public Innings(Team battingTeam, Team bowlingTeam) {
        this.battingTeam = battingTeam;
        this.bowlingTeam = bowlingTeam;
        this.score = 0;
        this.wickets = 0;
        this.balls = new ArrayList<>();
        this.playerStats = new ConcurrentHashMap<>();
        for(Player player: battingTeam.getPlayers()) {
            playerStats.put(player, new PlayerStats());
        }
        for(Player player: bowlingTeam.getPlayers()) {
            playerStats.put(player, new PlayerStats());
        }
    }

    public void addBall(Ball ball) {
        balls.add(ball);
        int runsScored = ball.getRunsScored();
        this.score += runsScored;
        if (ball.getExtraType() == ExtraType.WIDE || ball.getExtraType() == ExtraType.NO_BALL) {
            this.score += 1;
        } else {
            ball.getFacedBy().getStats().updateRuns(runsScored);
            ball.getFacedBy().getStats().incrementBallsPlayed();
            playerStats.get(ball.getFacedBy()).updateRuns(runsScored);
            playerStats.get(ball.getFacedBy()).incrementBallsPlayed();
        }
        if (ball.isWicket()) {
            this.wickets++;
            ball.getBowledBy().getStats().incrementWickets();
            playerStats.get(ball.getBowledBy()).incrementWickets();
        }
    }

    public void printPlayerStats() {
        for (Map.Entry<Player, PlayerStats> entry : playerStats.entrySet()) {
            Player player = entry.getKey();
            PlayerStats stats = entry.getValue();

            if (stats.getBallsPlayed() > 0 || stats.getWickets() > 0) {
                System.out.println("Player: " + player.getName() + " - Stats: " + stats);
            }
        }
    }

    public int getScore() { return score; }
    public int getWickets() { return wickets; }
    public Team getBattingTeam() { return battingTeam; }

    public double getOvers() {
        int validBalls = (int) balls.stream()
                .filter(b -> b.getExtraType() != ExtraType.WIDE && b.getExtraType() != ExtraType.NO_BALL)
                .count();

        int completedOvers = validBalls / 6;
        int ballsInCurrentOver = validBalls % 6;

        return completedOvers + (ballsInCurrentOver / 10.0);
    }
}