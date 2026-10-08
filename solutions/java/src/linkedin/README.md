# LinkedIn (LLD)

## Problem Statement

Design and implement a LinkedIn-like professional networking platform that allows users to create profiles, connect with others, post jobs, send messages, and receive notifications.

---

## Requirements

- **User Management:** Users can register, log in, and manage their profiles.
- **Profile Management:** Users can add education, experience, and skills to their profiles.
- **Connections:** Users can send and accept connection requests.
- **Job Posting:** Users (or companies) can post job openings.
- **Messaging:** Users can send direct messages to their connections.
- **Notifications:** The system notifies users of connection requests, job matches, messages, and other events.
- **Extensibility:** Easy to add new features such as endorsements, recommendations, or company pages.

---

## Implemented Classes and Services

- `LinkedInSystem` is the singleton facade. It registers and searches `Member` objects, manages connection requests, creates posts, and displays news feeds.
- `Member` is built with `Member.Builder` and contains a `Profile`, connections, and notifications. `Education` and `Experience` are profile entries.
- `ConnectionService` manages request IDs and acceptance; `NotificationService` delivers notifications.
- `Post`, `Like`, and `Comment` model news-feed content and interactions. `NewsFeedService` displays posts using a `FeedSortingStrategy`; the demo uses `ChronologicalSortStrategy`.
- `SearchService` searches registered members by name.

Login, job posting, and direct-message APIs are not implemented in this example; the requirements above describe the broader design goals.

## UML Class Diagram

![](../../../../class-diagrams/linkedin-class-diagram.png)

## Example Usage

```java
import linkedin.LinkedInSystem;
import linkedin.entities.Member;

LinkedInSystem system = LinkedInSystem.getInstance();
Member alice = new Member.Builder("Alice", "alice@example.com").build();
Member bob = new Member.Builder("Bob", "bob@example.com").build();
system.registerMember(alice);
system.registerMember(bob);
String requestId = system.sendConnectionRequest(alice, bob);
system.acceptConnectionRequest(requestId);
system.createPost(bob.getId(), "Hello from Bob!");
system.viewNewsFeed(alice.getId());
```

This fragment belongs inside a method. See `LinkedInDemo.java` for the complete demonstration, including profile construction, post interactions, notifications, and member search.
