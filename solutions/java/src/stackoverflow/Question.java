package stackoverflow;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.CopyOnWriteArrayList;

public class Question implements Votable, Commentable {
    private final String id;
    private final String title;
    private final String content;
    private final User author;
    private final Date creationDate;
    private final List<Answer> answers;
    private final List<Comment> comments;
    private final List<Tag> tags;
    private final List<Vote> votes;
    private Answer acceptedAnswer;

    public Question(User author, String title, String content, List<Tag> tags) {
        this.id = UUID.randomUUID().toString();
        this.author = author;
        this.title = title;
        this.content = content;
        this.creationDate = new Date();
        this.answers = new CopyOnWriteArrayList<>();
        this.votes = new CopyOnWriteArrayList<>();
        this.comments = new CopyOnWriteArrayList<>();
        this.tags = tags;
    }

    public synchronized void addAnswer(Answer answer) {
        answers.add(answer);
    }

    public synchronized void acceptAnswer(Answer answer) {
        this.acceptedAnswer = answer;
    }

    @Override
    public void vote(User voter, VoteType type) {
        votes.removeIf(v -> v.getVoter().equals(voter));
        votes.add(new Vote(voter, type));
        author.updateReputation(type == VoteType.UPVOTE ? ReputationType.QUESTION_UPVOTE.getPoints() :
                ReputationType.QUESTION_DOWNVOTE.getPoints());
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

    // Getters
    public String getId() { return id; }
    public User getAuthor() { return author; }
    public String getTitle() { return title; }
    public String getContent() { return content; }
    public List<Tag> getTags() { return new ArrayList<>(tags); }
}