package stackoverflow;

import stackoverflow.enums.VoteType;
import stackoverflow.entities.*;
import stackoverflow.observer.PostObserver;
import stackoverflow.observer.ReputationManager;
import stackoverflow.strategy.SearchStrategy;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class StackOverflowService {
    private final Map<String, User> users = new ConcurrentHashMap<>();
    private final Map<String, Question> questions = new ConcurrentHashMap<>();
    private final Map<String, Answer> answers = new ConcurrentHashMap<>();
    private final PostObserver reputationManager = new ReputationManager();

    public User createUser(String name) {
        User user = new User(name);
        users.put(user.getId(), user);
        return user;
    }

    public Question postQuestion(String userId, String title, String body, Set<Tag> tags) {
        User author = users.get(userId);
        Question question = new Question(title, body, author, tags);
        question.addObserver(reputationManager);
        questions.put(question.getId(), question);
        return question;
    }

    public Answer postAnswer(String userId, String questionId, String body) {
        User author = users.get(userId);
        Question question = questions.get(questionId);
        Answer answer = new Answer(body, author);
        answer.addObserver(reputationManager);
        question.addAnswer(answer);
        answers.put(answer.getId(), answer);
        return answer;
    }

    public void voteOnPost(String userId, String postId, VoteType voteType) {
        User user = users.get(userId);
        Post post = findPostById(postId);
        post.vote(user, voteType);
    }

    public void acceptAnswer(String questionId, String answerId) {
        Question question = questions.get(questionId);
        Answer answer = answers.get(answerId);
        question.acceptAnswer(answer);
    }

    public List<Question> searchQuestions(List<SearchStrategy> strategies) {
        List<Question> results = new ArrayList<>(questions.values());

        // Sequentially apply each filter strategy to the results of the previous one.
        for (SearchStrategy strategy : strategies) {
            results = strategy.filter(results);
        }

        return results;
    }

    public User getUser(String userId) {
        return users.get(userId);
    }

    private Post findPostById(String postId) {
        if (questions.containsKey(postId)) {
            return questions.get(postId);
        } else if (answers.containsKey(postId)) {
            return answers.get(postId);
        }

        throw new NoSuchElementException("Post not found");
    }
}