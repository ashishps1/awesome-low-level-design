package cricinfo;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class ScorecardService {
    private static ScorecardService instance;
    private final Map<String, Scorecard> scorecards;
    private final AtomicInteger scorecardIdCounter;

    private ScorecardService() {
        scorecards = new ConcurrentHashMap<>();
        scorecardIdCounter = new AtomicInteger(0);
    }

    public static synchronized ScorecardService getInstance() {
        if (instance == null) {
            instance = new ScorecardService();
        }
        return instance;
    }

    public synchronized void createScorecard(Match match) {
        String scorecardId = generateScorecardId(match.getId());
        Scorecard scorecard = new Scorecard(scorecardId, match);
        scorecards.put(scorecardId, scorecard);
    }

    public Scorecard getScorecard(String scorecardId) {
        return scorecards.get(scorecardId);
    }

    public void updateScore(String scorecardId, String teamId, int score) {
        Scorecard scorecard = scorecards.get(scorecardId);
        if (scorecard != null) {
            scorecard.updateScore(teamId, score);
        }
    }

    public void addInnings(String scorecardId, Innings innings) {
        Scorecard scorecard = scorecards.get(scorecardId);
        if (scorecard != null) {
            scorecard.addInnings(innings);
        }
    }

    private String generateScorecardId(String matchId) {
        int scorecardId = scorecardIdCounter.incrementAndGet();
        return "SC-" + matchId + "-" + String.format("%04d", scorecardId);
    }
}
