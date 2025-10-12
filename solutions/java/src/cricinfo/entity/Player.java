package cricinfo.entity;

import cricinfo.enums.PlayerRole;

public class Player {
    private final String id;
    private final String name;
    private final PlayerRole role;
    private PlayerStats stats;

    public Player(String id, String name, PlayerRole role) {
        this.id = id;
        this.name = name;
        this.role = role;
        this.stats = new PlayerStats();
    }

    public String getId() {
        return id;
    }

    public String getName() { return name; }

    public PlayerStats getStats() {
        return stats;
    }
}