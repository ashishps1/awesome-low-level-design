package cricinfo;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MatchService {
    private static MatchService instance;
    private final Map<String, Match> matches;

    private MatchService() {
        matches = new ConcurrentHashMap<>();
    }

    public static synchronized MatchService getInstance() {
        if (instance == null) {
            instance = new MatchService();
        }
        return instance;
    }

    public void addMatch(Match match) {
        matches.put(match.getId(), match);
    }

    public Match getMatch(String matchId) {
        return matches.get(matchId);
    }

    public List<Match> getAllMatches() {
        return new ArrayList<>(matches.values());
    }

    public void updateMatchStatus(String matchId, MatchStatus status) {
        Match match = matches.get(matchId);
        if (match != null) {
            match.setStatus(status);
        }
    }
}
