package cricinfo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Scorecard {
    private final String id;
    private final Match match;
    private final Map<String, Integer> teamScores;
    private final List<Innings> innings;

    public Scorecard(String id, Match match) {
        this.id = id;
        this.match = match;
        this.teamScores = new HashMap<>();
        this.innings = new ArrayList<>();
    }

    public void updateScore(String teamId, int score) {
        teamScores.put(teamId, score);
    }

    public void addInnings(Innings innings) {
        this.innings.add(innings);
    }

    public String getId() {
        return id;
    }

    public Match getMatch() {
        return match;
    }

    public Map<String, Integer> getTeamScores() {
        return teamScores;
    }

    public List<Innings> getInnings() {
        return innings;
    }
}
