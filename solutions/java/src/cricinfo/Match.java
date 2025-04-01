package cricinfo;

import java.time.LocalDateTime;
import java.util.List;

public class Match {
    private final String id;
    private final String title;
    private final String venue;
    private final LocalDateTime startTime;
    private final List<Team> teams;
    private MatchStatus status;
    private Scorecard scorecard;

    public Match(String id, String title, String venue, LocalDateTime startTime, List<Team> teams) {
        this.id = id;
        this.title = title;
        this.venue = venue;
        this.startTime = startTime;
        this.teams = teams;
        this.status = MatchStatus.SCHEDULED;
    }

    public String getId() {
        return id;
    }

    public void setStatus(MatchStatus status) {
        this.status = status;
    }

    public String getTitle() {
        return title;
    }
}
