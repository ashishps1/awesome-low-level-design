package stackoverflow;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class StackOverflow {
    private static StackOverflow instance;
    private final Map<Integer, User> users;
    private final Map<Integer, Question> questions;
    private final Map<String, List<Question>> taggedQuestions;

    private StackOverflow() {
        users = new ConcurrentHashMap<>();
        questions = new ConcurrentHashMap<>();
        taggedQuestions = new ConcurrentHashMap<>();
    }

    public static synchronized StackOverflow getInstance() {
        if (instance == null) {
            instance = new StackOverflow();
        }
        return instance;
    }

    public void registerUser(User user) {
        users.put(user.getId(), user);
    }

    public User loginUser(String username, String password) {
        for (User user : users.values()) {
            if (user.getUsername().equals(username) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    public void postQuestion(Question question) {
        questions.put(question.getId(), question);
        for (Tag tag : question.getTags()) {
            taggedQuestions.computeIfAbsent(tag.getName(), k -> new ArrayList<>()).add(question);
        }
    }

    public void postAnswer(Answer answer) {
        Question question = answer.getQuestion();
        question.getAnswers().add(answer);
    }

    public void postComment(Comment comment) {
        // Add comment to the respective question or answer
        // ...
    }

    public void voteQuestion(Question question, int value) {
        synchronized (question) {
            question.setVoteCount(question.getVoteCount() + value);
        }
        updateUserReputation(question.getAuthor(), value);
    }

    public void voteAnswer(Answer answer, int value) {
        synchronized (answer) {
            answer.setVoteCount(answer.getVoteCount() + value);
        }
        updateUserReputation(answer.getAuthor(), value);
    }

    private void updateUserReputation(User user, int value) {
        synchronized (user) {
            user.setReputation(user.getReputation() + value);
        }
    }

    public List<Question> searchQuestions(String query) {
        List<Question> results = new ArrayList<>();
        for (Question question : questions.values()) {
            if (question.getTitle().contains(query) || question.getBody().contains(query)) {
                results.add(question);
            }
        }
        return results;
    }

    public List<Question> getQuestionsByTag(String tagName) {
        return taggedQuestions.getOrDefault(tagName, new ArrayList<>());
    }

    public List<Question> getQuestionsByUser(User user) {
        List<Question> results = new ArrayList<>();
        for (Question question : questions.values()) {
            if (question.getAuthor().equals(user)) {
                results.add(question);
            }
        }
        return results;
    }
}
