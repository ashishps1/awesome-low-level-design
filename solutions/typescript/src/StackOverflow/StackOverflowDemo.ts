import StackOverflow from "./StackOverflow";
import { VoteTypeEnum } from "./VoteTypeEnum";

export default class StackOverflowDemo {
  static run() {
    const stackOverflow = StackOverflow.getInstance();

    // Create users
    const alice = stackOverflow.createUser("Alice", "alice@example.com");
    const bob = stackOverflow.createUser("Bob", "bob@example.com");
    const charlie = stackOverflow.createUser("Charlie", "charlie@example.com");

    // Alice asks a question
    const javaQuestion = stackOverflow.postQuestion(
      alice.getUserId(),
      "Why does typeof null return 'object'?",
      "I tried `typeof null` and got 'object'. I expected 'null'. Is this a bug or feature?",
      ["javascript", "typeof", "null"],
    );

    // Bob answers Alice's question
    const bobAnswer = stackOverflow.postAnswer(
      bob.getUserId(),
      javaQuestion.getId(),
      "`typeof null` returns 'object' due to a bug in JavaScript's early implementation. It’s now a legacy quirk, and changing it would break existing code.",
    );

    // Charlie comments on the question
    stackOverflow.addComment(
      charlie.getUserId(),
      javaQuestion,
      "Welcome to JavaScript! Where 'null' is an object and 'undefined' means everything and nothing. 😅",
    );

    // Alice comments on Bob's answer
    stackOverflow.addComment(
      alice.getUserId(),
      bobAnswer,
      "Wow, that's weird but helpful. Thanks Bob!",
    );

    // Charlie votes on the question and answer
    stackOverflow.vote(charlie.getUserId(), javaQuestion, VoteTypeEnum.UPVOTE);
    stackOverflow.vote(charlie.getUserId(), bobAnswer, VoteTypeEnum.UPVOTE);

    // Alice accepts Bob's answer
    stackOverflow.acceptAnswer(bobAnswer.getId());

    // Print out the current state
    console.log("Question: " + javaQuestion.getTitle());
    console.log("Asked by: " + javaQuestion.getAuthor().getName());
    console.log(
      "Tags: " +
        javaQuestion
          .getTags()
          .map((tag) => tag.getName())
          .join(", "),
    );
    console.log("Votes: " + javaQuestion.getVoteCount());
    console.log("Comments: " + javaQuestion.getComments().length);
    console.log("\nAnswer by " + bobAnswer.getAuthor().getName() + ":");
    console.log(bobAnswer.getContent());
    console.log("Votes: " + bobAnswer.getVoteCount());
    console.log("Accepted: " + bobAnswer.getIsAccepted());
    console.log("Comments: " + bobAnswer.getComments().length);

    console.log("\nUser Reputations:");
    console.log("Alice: " + alice.getReputation());
    console.log("Bob: " + bob.getReputation());
    console.log("Charlie: " + charlie.getReputation());

    // Search questions by keyword
    console.log("\nSearch Results for 'javascript':");
    const searchResults = stackOverflow.searchQuestions("javascript");
    for (const q of searchResults) {
      console.log(q.getTitle());
    }

    // Search questions by user
    console.log("\nAlice's Questions:");
    const bobQuestions = stackOverflow.getQuestionsByUser(alice.getUserId());
    for (const q of bobQuestions) {
      console.log(q.getTitle());
    }
  }
}
