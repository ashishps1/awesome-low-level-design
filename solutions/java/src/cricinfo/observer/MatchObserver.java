package cricinfo.observer;

import cricinfo.entity.Match;
import cricinfo.entity.Ball;

public interface MatchObserver {
    void update(Match match, Ball lastBall);
}
