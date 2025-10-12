package cricinfo.entity;

import java.util.List;

public class Team {
    private final String id;
    private final String name;
    private final List<Player> players;

    public Team(String id, String name, List<Player> players) {
        this.id = id;
        this.name = name;
        this.players = players;
    }
    public String getName() { return name; }

    public List<Player> getPlayers() { return players; }
}
