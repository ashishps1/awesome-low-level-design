package stackoverflow.observer;

import stackoverflow.entities.Event;
import stackoverflow.entities.User;

public class ReputationManager implements PostObserver {
    private static final int QUESTION_UPVOTE_REP = 5;
    private static final int ANSWER_UPVOTE_REP = 10;
    private static final int ACCEPTED_ANSWER_REP = 15;
    private static final int DOWNVOTE_REP_PENALTY = -1; // Penalty for the voter
    private static final int POST_DOWNVOTED_REP_PENALTY = -2; // Penalty for the post author

    @Override
    public void onPostEvent(Event event) {
        User postAuthor = event.getTargetPost().getAuthor();
        switch (event.getType()) {
            case UPVOTE_QUESTION:
                postAuthor.updateReputation(QUESTION_UPVOTE_REP);
                break;
            case DOWNVOTE_QUESTION:
                postAuthor.updateReputation(DOWNVOTE_REP_PENALTY);
                event.getActor().updateReputation(POST_DOWNVOTED_REP_PENALTY); // voter penalty
                break;
            case UPVOTE_ANSWER:
                postAuthor.updateReputation(ANSWER_UPVOTE_REP);
                break;
            case DOWNVOTE_ANSWER:
                postAuthor.updateReputation(DOWNVOTE_REP_PENALTY);
                event.getActor().updateReputation(POST_DOWNVOTED_REP_PENALTY);
                break;
            case ACCEPT_ANSWER:
                postAuthor.updateReputation(ACCEPTED_ANSWER_REP);
                break;
        }
    }
}
