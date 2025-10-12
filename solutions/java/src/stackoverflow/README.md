# StackOverflow System (LLD)

## Problem Statement

Design and implement a simplified StackOverflow-like Q&A platform. The system should allow users to post questions and answers, vote on them, comment, tag questions, and track user reputation.

---

## Requirements

- **User Management:** Users can ask questions, answer, comment, and vote.
- **Questions & Answers:** Users can post questions and answers. Each question can have multiple answers, and one accepted answer.
- **Voting:** Users can upvote or downvote questions and answers. Reputation is updated accordingly.
- **Comments:** Users can comment on both questions and answers.
- **Tags:** Questions can be tagged for categorization.
- **Reputation:** Users gain or lose reputation based on votes and accepted answers.
- **Accepted Answer:** The question author can mark one answer as accepted.

---

## Core Entities

- **User:** Represents a user, tracks reputation and user details.
- **Question:** Represents a question, holds answers, comments, tags, votes, and accepted answer.
- **Answer:** Represents an answer to a question, holds comments, votes, and accepted status.
- **Comment:** Represents a comment on a question or answer.
- **Tag:** Represents a tag for categorizing questions.
- **Vote:** Represents a vote (upvote/downvote) by a user on a question or answer.
- **VoteType:** Enum for UPVOTE and DOWNVOTE.
- **Votable (interface):** For entities that can be voted on.
- **Commentable (interface):** For entities that can be commented on.

---

## Class Design

## UML Class Diagram

![](../../../../uml-diagrams/class-diagrams/stackoverflow-class-diagram.png)

### 1. User
- **Fields:** id, name, reputation, etc.
- **Methods:** updateReputation(int delta), getReputation(), etc.

### 2. Question
- **Fields:** id, title, content, author, creationDate, answers, comments, tags, votes, acceptedAnswer
- **Methods:** addAnswer(Answer), acceptAnswer(Answer), vote(User, VoteType), getVoteCount(), addComment(Comment), getComments(), etc.

### 3. Answer
- **Fields:** id, content, author, question, isAccepted, creationDate, comments, votes
- **Methods:** vote(User, VoteType), getVoteCount(), addComment(Comment), getComments(), markAsAccepted(), etc.

### 4. Comment
- **Fields:** id, content, author, creationDate

### 5. Tag
- **Fields:** name

### 6. Vote
- **Fields:** voter, type (VoteType)
- **Methods:** getVoter(), getType()

### 7. VoteType
- Enum: UPVOTE, DOWNVOTE

### 8. Votable (interface)
- **Methods:** vote(User, VoteType), getVoteCount()

### 9. Commentable (interface)
- **Methods:** addComment(Comment), getComments()

---

## Design Patterns Used

- **Strategy Pattern:** For voting and commenting behaviors via interfaces.
- **Observer Pattern:** (Conceptually) for reputation updates on votes and accepted answers.

---

## Example Usage

```java
User alice = new User("Alice");
Question q = new Question(alice, "What is Java?", "Explain Java basics.", Arrays.asList("java", "basics"));
User bob = new User("Bob");
Answer a = new Answer(bob, q, "Java is a programming language.");
q.addAnswer(a);
q.vote(bob, VoteType.UPVOTE);
a.vote(alice, VoteType.UPVOTE);
q.acceptAnswer(a);
```

---

## Demo

See `StackOverflowDemo.java` for a sample usage of the StackOverflow system.

---

## Extending the Framework

- **Add new features:** Such as badges, user profiles, or advanced search.
- **Add new vote types:** Extend `VoteType` and update logic in `vote()` methods.
- **Add moderation:** Implement admin/moderator roles for content management.

---