package stackoverflow;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class StackOverflow {
    private static StackOverflow instance;
    private final Map<String, User> users;
    private final Map<String, Question> questions;
    private final Map<String, Answer> answers;
    private final Map<String, Tag> tags;

    private StackOverflow() {
        users = new ConcurrentHashMap<>();
        questions = new ConcurrentHashMap<>();
        answers = new ConcurrentHashMap<>();
        tags = new ConcurrentHashMap<>();
    }

    public static synchronized StackOverflow getInstance() {
        if (instance == null) {
            instance = new StackOverflow();
        }
        return instance;
    }

    public User createUser(String username, String email) {
        User user = new User(username, email);
        users.put(user.getUserId(), user);
        return user;
    }

    public Question postQuestion(String userId, String title, String content, List<String> questionTags) {
        User author = users.get(userId);
        List<Tag> tagList = new ArrayList<>();
        for (String qTag: questionTags) {
            Tag tag = tags.getOrDefault(qTag, new Tag(qTag));
            tagList.add(tag);
            tags.put(tag.getId(), tag);
        }
        Question question = new Question(author, title, content, tagList);
        questions.put(question.getId(), question);
        return question;
    }

    public Answer postAnswer(String userId, String questionId, String content) {
        User author = users.get(userId);
        Question question = questions.get(questionId);
        Answer answer = new Answer(author, question, content);
        question.addAnswer(answer);
        answers.put(answer.getId(), answer);
        return answer;
    }

    public Comment addComment(String userId, Commentable commentable, String content) {
        User author = users.get(userId);
        Comment comment = new Comment(author, content);
        commentable.addComment(new Comment(author, content));
        return comment;
    }

    public void vote(String userId, Votable votable, VoteType voteType) {
        User user = users.get(userId);
        votable.vote(user, voteType);
    }

    public void acceptAnswer(String answerId) {
        Answer answer = answers.get(answerId);
        Question question = answer.getQuestion();
        answer.markAsAccepted();
        question.acceptAnswer(answer);
    }

    public List<Question> searchQuestions(String query) {
        return questions.values().stream()
                .filter(q -> q.getTitle().toLowerCase().contains(query.toLowerCase()) ||
                        q.getContent().toLowerCase().contains(query.toLowerCase()) ||
                        q.getTags().stream().anyMatch(t -> t.getName().equalsIgnoreCase(query)))
                .collect(Collectors.toList());
    }

    public List<Question> getQuestionsByUser(String userId) {
        User user = users.get(userId);
        return questions.values().stream()
                .filter(q -> q.getAuthor().equals(user))
                .toList();
    }
}