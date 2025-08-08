package cricinfo;

import cricinfo.enums.PlayerRole;
import cricinfo.entity.Ball;
import cricinfo.entity.Match;
import cricinfo.entity.Player;
import cricinfo.entity.Team;
import cricinfo.observer.MatchObserver;
import cricinfo.repository.MatchRepository;
import cricinfo.repository.PlayerRepository;
import cricinfo.state.FinishedState;
import cricinfo.state.LiveState;
import cricinfo.strategy.MatchFormatStrategy;

import java.util.UUID;

public class CricInfoService {
    private static volatile CricInfoService instance;
    private final MatchRepository matchRepository;
    private final PlayerRepository playerRepository;

    private CricInfoService() {
        this.matchRepository = new MatchRepository();
        this.playerRepository = new PlayerRepository();
    }

    public static CricInfoService getInstance() {
        if (instance == null) {
            synchronized (CricInfoService.class) {
                if (instance == null) {
                    instance = new CricInfoService();
                }
            }
        }
        return instance;
    }

    public Match createMatch(Team team1, Team team2, MatchFormatStrategy format) {
        String matchId = UUID.randomUUID().toString();
        Match match = new Match(matchId, team1, team2, format);
        matchRepository.save(match);
        System.out.printf("Match %s created between %s and %s.%n", format.getFormatName(), team1.getName(), team2.getName());
        return match;
    }

    public void startMatch(String matchId) {
        matchRepository.findById(matchId).ifPresent(match -> {
            match.setState(new LiveState());
            System.out.printf("Match %s is now LIVE.%n", matchId);
        });
    }

    public void processBallUpdate(String matchId, Ball ball) {
        matchRepository.findById(matchId).ifPresent(match -> match.processBall(ball));
    }

    public void startNextInnings(String matchId) {
        matchRepository.findById(matchId).ifPresent(Match::startNextInnings);
    }

    public void subscribeToMatch(String matchId, MatchObserver observer) {
        matchRepository.findById(matchId).ifPresent(match -> match.addObserver(observer));
    }

    public void endMatch(String matchId) {
        matchRepository.findById(matchId).ifPresent(match -> {
            match.setState(new FinishedState());
            System.out.printf("Match %s has FINISHED.%n", matchId);
        });
    }

    public Player addPlayer(String playerId, String playerName, PlayerRole playerRole) {
        Player player = new Player(playerId, playerName, playerRole);
        playerRepository.save(player);
        return player;
    }
}
