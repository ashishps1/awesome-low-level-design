package cricinfo.entity;

import cricinfo.enums.WicketType;

public class Wicket {
    private final WicketType wicketType;
    private final Player playerOut;
    private final Player caughtBy;
    private final Player runoutBy;

    private Wicket(Builder builder) {
        this.wicketType = builder.wicketType;
        this.playerOut = builder.playerOut;
        this.caughtBy = builder.caughtBy;
        this.runoutBy = builder.runoutBy;
    }

    public WicketType getWicketType() { return wicketType; }
    public Player getPlayerOut() { return playerOut; }
    public Player getCaughtBy() { return caughtBy; }
    public Player getRunoutBy() { return runoutBy; }

    public static class Builder {
        // Required parameters
        private final WicketType wicketType;
        private final Player playerOut;

        // Optional parameters
        private Player caughtBy = null;
        private Player runoutBy = null;

        public Builder(WicketType wicketType, Player playerOut) {
            this.wicketType = wicketType;
            this.playerOut = playerOut;
        }

        public Builder caughtBy(Player player) {
            this.caughtBy = player;
            return this;
        }

        public Builder runoutBy(Player player) {
            this.runoutBy = player;
            return this;
        }

        public Wicket build() {
            // We could add validation here, e.g., ensure 'caughtBy' is only set for WicketType.CAUGHT
            return new Wicket(this);
        }
    }
}