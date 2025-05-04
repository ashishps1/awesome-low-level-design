package stackoverflow;

public interface Votable {
    void vote(User voter, VoteType type);
    int getVoteCount();
}
