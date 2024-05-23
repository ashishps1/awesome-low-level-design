package stackoverflow;

import java.util.List;

public class Question {
    private int id;
    private String title;
    private String body;
    private User author;
    private List<Answer> answers;
    private List<Comment> comments;
    private List<Tag> tags;
    private int voteCount;

    public Question(int id, String title, String body, User author, List<Answer> answers, List<Comment> comments, List<Tag> tags, int voteCount) {
        this.id = id;
        this.title = title;
        this.body = body;
        this.author = author;
        this.answers = answers;
        this.comments = comments;
        this.tags = tags;
        this.voteCount = voteCount;
    }

    public void setVoteCount(int voteCount) {
        this.voteCount = voteCount;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getBody() {
        return body;
    }

    public User getAuthor() {
        return author;
    }

    public List<Answer> getAnswers() {
        return answers;
    }

    public List<Comment> getComments() {
        return comments;
    }

    public List<Tag> getTags() {
        return tags;
    }

    public int getVoteCount() {
        return voteCount;
    }
}
