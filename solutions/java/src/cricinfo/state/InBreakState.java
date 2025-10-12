package cricinfo.state;

import cricinfo.enums.MatchStatus;
import cricinfo.entity.Ball;
import cricinfo.entity.Match;

public class InBreakState implements MatchState {
    @Override
    public void processBall(Match match, Ball ball) {
        System.out.println("ERROR: Cannot process a ball. The match is currently in a break.");
    }

    @Override
    public void startNextInnings(Match match) {
        System.out.println("Starting the next innings...");
        match.createNewInnings();
        match.setState(new LiveState());
        match.setCurrentStatus(MatchStatus.LIVE);
    }
}
