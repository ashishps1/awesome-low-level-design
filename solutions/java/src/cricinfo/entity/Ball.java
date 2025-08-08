package cricinfo.entity;

import cricinfo.CommentaryManager;
import cricinfo.enums.ExtraType;

public class Ball {
    private final int ballNumber;
    private final Player bowledBy;
    private final Player facedBy;
    private final int runsScored;
    private final Wicket wicket; // Null if no wicket
    private final ExtraType extraType; // Null if no extra
    private final String commentary;

    private Ball(BallBuilder builder) {
        this.ballNumber = builder.ballNumber;
        this.bowledBy = builder.bowledBy;
        this.facedBy = builder.facedBy;
        this.runsScored = builder.runsScored;
        this.wicket = builder.wicket;
        this.extraType = builder.extraType;
        this.commentary = builder.commentary;
    }

    public boolean isWicket() { return wicket != null; }
    public boolean isBoundary() { return runsScored == 4 || runsScored == 6; }
    public String getCommentary() { return commentary; }
    public int getRunsScored() { return runsScored; }
    public Player getFacedBy() { return facedBy; }
    public Player getBowledBy() { return bowledBy; }
    public Wicket getWicket() { return wicket; }

    public ExtraType getExtraType() {
        return extraType;
    }
    // Other getters

    public static class BallBuilder {
        private int ballNumber;
        private Player bowledBy;
        private Player facedBy;
        private int runsScored;
        private Wicket wicket;
        private ExtraType extraType;
        private String commentary;

        public BallBuilder withBallNumber(int ballNumber) { this.ballNumber = ballNumber; return this; }
        public BallBuilder bowledBy(Player bowler) { this.bowledBy = bowler; return this; }
        public BallBuilder facedBy(Player batsman) { this.facedBy = batsman; return this; }
        public BallBuilder withRuns(int runs) { this.runsScored = runs; return this; }
        public BallBuilder withWicket(Wicket wicket) { this.wicket = wicket; return this; }
        public BallBuilder withExtraType(ExtraType extra) { this.extraType = extra; return this; }
        public BallBuilder withCommentary(String commentary) { this.commentary = commentary; return this; }

        public Ball build() {
            // This is needed because the manager needs the ball's final state to generate commentary
            Ball tempBall = new Ball(this);

            if (this.commentary == null) {
                this.commentary = CommentaryManager.getInstance().generateCommentary(tempBall);
            }

            return new Ball(this);
        }
    }
}
