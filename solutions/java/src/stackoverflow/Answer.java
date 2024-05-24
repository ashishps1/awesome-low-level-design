package stackoverflow;

import java.util.List;

public class Answer {
    private final int id;
    private final String body;
    private final User author;
    private final Question question;
    private final List<Comment> comments;
    private int voteCount;

    public Answer(int id, String body, User author, Question question, List<Comment> comments, int voteCount) {
        this.id = id;
        this.body = body;
        this.author = author;
        this.question = question;
        this.comments = comments;
        this.voteCount = voteCount;
    }

    public void setVoteCount(int voteCount) {
        this.voteCount = voteCount;
    }

    public int getId() {
        return id;
    }

    public String getBody() {
        return body;
    }

    public User getAuthor() {
        return author;
    }

    public Question getQuestion() {
        return question;
    }

    public List<Comment> getComments() {
        return comments;
    }

    public int getVoteCount() {
        return voteCount;
    }
}
