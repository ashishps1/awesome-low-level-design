package stackoverflow;

public enum ReputationType {
    QUESTION_UPVOTE(5),
    QUESTION_DOWNVOTE(-2),
    ANSWER_UPVOTE(10),
    ANSWER_DOWNVOTE(-2),
    ANSWER_ACCEPTED(15);

    private final int points;

    ReputationType(int points) {
        this.points = points;
    }

    public int getPoints() {
        return points;
    }
}