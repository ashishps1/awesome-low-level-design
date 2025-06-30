package stackoverflow;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.UUID;

public class Answer implements Votable, Commentable {
    private final String id;
    private final String content;
    private final User author;
    private final Question question;
    private boolean isAccepted;
    private final Date creationDate;
    private final List<Comment> comments;
    private final List<Vote> votes;

    public Answer(User author, Question question, String content) {
        this.id = UUID.randomUUID().toString();
        this.author = author;
        this.question = question;
        this.content = content;
        this.creationDate = new Date();
        this.votes = new ArrayList<>();
        this.comments = new ArrayList<>();
        this.isAccepted = false;
    }

    @Override
    public void vote(User voter, VoteType type) {
        votes.removeIf(v -> v.getVoter().equals(voter));
        votes.add(new Vote(voter, type));
        author.updateReputation(type == VoteType.UPVOTE ? ReputationType.ANSWER_UPVOTE.getPoints() :
                ReputationType.ANSWER_DOWNVOTE.getPoints());
    }

    @Override
    public int getVoteCount() {
        return votes.stream()
                .mapToInt(v -> v.getType().getValue())
                .sum();
    }

    @Override
    public void addComment(Comment comment) {
        comments.add(comment);
    }

    @Override
    public List<Comment> getComments() {
        return new ArrayList<>(comments);
    }

    public Question getQuestion() {
        return question;
    }

    public void markAsAccepted() {
        if (isAccepted) {
            throw new IllegalStateException("This answer is already accepted");
        }
        isAccepted = true;
        author.updateReputation(ReputationType.ANSWER_ACCEPTED.getPoints());
    }

    // Getters
    public String getId() { return id; }
    public User getAuthor() { return author; }
    public String getContent() { return content; }
    public boolean isAccepted() { return isAccepted; }
}