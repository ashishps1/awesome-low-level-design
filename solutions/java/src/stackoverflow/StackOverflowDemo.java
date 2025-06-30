package stackoverflow;

import java.util.Arrays;
import java.util.List;

public class StackOverflowDemo {
    public static void run() {
        StackOverflow stackOverflow = StackOverflow.getInstance();

        // Create users
        User alice = stackOverflow.createUser("Alice", "alice@example.com");
        User bob = stackOverflow.createUser("Bob", "bob@example.com");
        User charlie = stackOverflow.createUser("Charlie", "charlie@example.com");

        // Alice asks a question
        Question javaQuestion = stackOverflow.postQuestion(alice.getUserId(), "What is polymorphism in Java?",
                "Can someone explain polymorphism in Java with an example?",
                Arrays.asList("java", "oop"));

        // Bob answers Alice's question
        Answer bobAnswer = stackOverflow.postAnswer(bob.getUserId(), javaQuestion.getId(),
                "Polymorphism in Java is the ability of an object to take on many forms...");

        // Charlie comments on the question
        stackOverflow.addComment(charlie.getUserId(), javaQuestion, "Great question! I'm also interested in learning about this.");

        // Alice comments on Bob's answer
        stackOverflow.addComment(alice.getUserId(), bobAnswer, "Thanks for the explanation! Could you provide a code example?");

        // Charlie votes on the question and answer
        stackOverflow.vote(charlie.getUserId(), javaQuestion, VoteType.UPVOTE);
        stackOverflow.vote(charlie.getUserId(), bobAnswer, VoteType.UPVOTE);

        // Alice accepts Bob's answer
        stackOverflow.acceptAnswer(bobAnswer.getId());

        // Print out the current state
        System.out.println("Question: " + javaQuestion.getTitle());
        System.out.println("Asked by: " + javaQuestion.getAuthor().getName());
        System.out.println("Tags: " + javaQuestion.getTags().stream().map(Tag::getName).reduce((a, b) -> a + ", " + b).orElse(""));
        System.out.println("Votes: " + javaQuestion.getVoteCount());
        System.out.println("Comments: " + javaQuestion.getComments().size());
        System.out.println("\nAnswer by " + bobAnswer.getAuthor().getName() + ":");
        System.out.println(bobAnswer.getContent());
        System.out.println("Votes: " + bobAnswer.getVoteCount());
        System.out.println("Accepted: " + bobAnswer.isAccepted());
        System.out.println("Comments: " + bobAnswer.getComments().size());

        System.out.println("\nUser Reputations:");
        System.out.println("Alice: " + alice.getReputation());
        System.out.println("Bob: " + bob.getReputation());
        System.out.println("Charlie: " + charlie.getReputation());

        // Search questions by keyword
        System.out.println("\nSearch Results for 'java':");
        List<Question> searchResults = stackOverflow.searchQuestions("java");
        for (Question q : searchResults) {
            System.out.println(q.getTitle());
        }

        // Search questions by user
        System.out.println("\nAlice's Questions:");
        List<Question> bobQuestions = stackOverflow.getQuestionsByUser(alice.getUserId());
        for (Question q : bobQuestions) {
            System.out.println(q.getTitle());
        }
    }
}
