package stackoverflow;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class StackOverflowDemo {
    public static void run() {
        StackOverflow stackOverflow = StackOverflow.getInstance();

        // Register users
        User user1 = new User(1, "john", "password123", "john@example.com", 0);
        User user2 = new User(2, "jane", "password456", "jane@example.com", 0);
        stackOverflow.registerUser(user1);
        stackOverflow.registerUser(user2);

        // User login
        User loggedInUser = stackOverflow.loginUser("john", "password123");
        if (loggedInUser != null) {
            System.out.println("User logged in: " + loggedInUser.getUsername());
        } else {
            System.out.println("Invalid username or password.");
        }

        // Post a question
        Question question1 = new Question(1, "What is Java?", "Please explain Java.", user1, new ArrayList<>(),
                new ArrayList<>(), Arrays.asList(new Tag(1, "java"), new Tag(2, "programming")), 0);
        stackOverflow.postQuestion(question1);

        // Post an answer
        Answer answer1 = new Answer(1, "Java is an object-oriented programming language.", user2, question1,
                new ArrayList<>(), 0);
        stackOverflow.postAnswer(answer1);

        // Vote on the question
        stackOverflow.voteQuestion(question1, 1);

        // Search for questions
        List<Question> searchResults = stackOverflow.searchQuestions("Java");
        System.out.println("Search Results:");
        for (Question question : searchResults) {
            System.out.println(question.getTitle());
        }

        // Get questions by tag
        List<Question> taggedQuestions = stackOverflow.getQuestionsByTag("java");
        System.out.println("Questions tagged with 'java':");
        for (Question question : taggedQuestions) {
            System.out.println(question.getTitle());
        }

        // Get questions by user
        List<Question> userQuestions = stackOverflow.getQuestionsByUser(user1);
        System.out.println("Questions posted by user1:");
        for (Question question : userQuestions) {
            System.out.println(question.getTitle());
        }
    }
}
