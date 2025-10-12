package cricinfo.state;

import cricinfo.enums.MatchStatus;
import cricinfo.entity.Innings;
import cricinfo.entity.Match;
import cricinfo.entity.Ball;
import cricinfo.entity.Team;

public class LiveState implements MatchState {
    @Override
    public void processBall(Match match, Ball ball) {
        // 1. Process the ball as usual
        Innings currentInnings = match.getCurrentInnings();
        currentInnings.addBall(ball);
        match.notifyObservers(ball); // Notify observers about this specific ball
        // 2. Check for win/end conditions
        checkForMatchEnd(match);
    }

    private void checkForMatchEnd(Match match) {
        Innings currentInnings = match.getCurrentInnings();
        int inningsCount = match.getInnings().size();
        boolean isFinalInnings = (inningsCount == match.getFormatStrategy().getTotalInnings());

        // --- A. WIN CONDITION: Chasing team surpasses the target ---
        if (isFinalInnings) {
            int targetScore = match.getInnings().get(0).getScore() + 1;
            if (currentInnings.getScore() >= targetScore) {
                int wicketsRemaining = (currentInnings.getBattingTeam().getPlayers().size() - 1) - currentInnings.getWickets();
                declareWinner(match, currentInnings.getBattingTeam(), "won by " + wicketsRemaining + " wickets");
                return; // Match is over
            }
        }

        // --- B. END OF INNINGS CONDITION: All out or overs completed ---
        if (isInningsOver(match)) {
            if (isFinalInnings) {
                // The whole match is over, determine winner by runs or a tie
                int score1 = match.getInnings().get(0).getScore();
                int score2 = currentInnings.getScore();

                if (score1 > score2) {
                    declareWinner(match, match.getTeam1(), "won by " + (score1 - score2) + " runs");
                } else if (score2 > score1) {
                    // This case is technically handled above, but is a good safeguard.
                    int wicketsRemaining = (currentInnings.getBattingTeam().getPlayers().size() - 1) - currentInnings.getWickets();
                    declareWinner(match, currentInnings.getBattingTeam(), "won by " + wicketsRemaining + " wickets");
                } else {
                    declareWinner(match, null, "Match Tied"); // No winner in a tie
                }
            } else {
                // It's just an innings break, not the end of the match
                System.out.println("End of the innings!");
                match.setState(new InBreakState());
                match.setCurrentStatus(MatchStatus.IN_BREAK);
                match.notifyObservers(null); // Signal innings break to observers
            }
        }
    }

    private void declareWinner(Match match, Team winningTeam, String message) {
        System.out.println("MATCH FINISHED!");
        match.setWinner(winningTeam);
        String resultMessage = (winningTeam != null) ? winningTeam.getName() + " " + message : message;
        match.setResultMessage(resultMessage);

        match.setState(new FinishedState());
        match.setCurrentStatus(MatchStatus.FINISHED);
        match.notifyObservers(null); // Signal match end to observers
    }

    private boolean isInningsOver(Match match) {
        Innings currentInnings = match.getCurrentInnings();
        // Condition 1: A team with 11 players is all out when 10 wickets fall.
        boolean allOut = currentInnings.getWickets() >= currentInnings.getBattingTeam().getPlayers().size() - 1;
        // Condition 2: All overs have been bowled
        boolean oversFinished = (int) currentInnings.getOvers() >= match.getFormatStrategy().getTotalOvers();
        return allOut || oversFinished;
    }
}