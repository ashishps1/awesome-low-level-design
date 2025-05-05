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

## Core Entities

- **LinkedInService:** Main class that manages users, connections, job postings, messages, and notifications.
- **User:** Represents a user with profile, connections, messages, and notifications.
- **Profile:** Represents a user's professional profile, including education, experience, and skills.
- **Connection:** Represents a connection between two users.
- **JobPosting:** Represents a job posted by a user or company.
- **Message:** Represents a direct message between users.
- **Notification:** Represents a notification sent to a user.
- **NotificationType (enum):** Types of notifications (e.g., CONNECTION_REQUEST, JOB_MATCH, MESSAGE).
- **Skill:** Represents a skill in a user's profile.
- **Education:** Represents an education entry in a user's profile.
- **Experience:** Represents a work experience entry in a user's profile.

---

## Class Design

### 1. LinkedInService
- **Fields:** List<User> users, List<JobPosting> jobPostings, List<Connection> connections, List<Notification> notifications
- **Methods:** registerUser(User), addConnection(User, User), postJob(JobPosting), sendMessage(User, User, String), sendNotification(Notification), searchUsers(String), searchJobs(String), etc.

### 2. User
- **Fields:** int id, String name, Profile profile, List<Connection> connections, List<Message> messages, List<Notification> notifications
- **Methods:** sendConnectionRequest(User), acceptConnection(Connection), sendMessage(User, String), addSkill(Skill), addEducation(Education), addExperience(Experience), etc.

### 3. Profile
- **Fields:** List<Skill> skills, List<Education> education, List<Experience> experience

### 4. Connection
- **Fields:** int id, User user1, User user2, boolean isAccepted

### 5. JobPosting
- **Fields:** int id, String title, String description, User postedBy

### 6. Message
- **Fields:** int id, User sender, User receiver, String content

### 7. Notification
- **Fields:** int id, User recipient, String message, NotificationType type

### 8. NotificationType (enum)
- Values: CONNECTION_REQUEST, JOB_MATCH, MESSAGE, etc.

### 9. Skill
- **Fields:** String name

### 10. Education
- **Fields:** String institution, String degree, String fieldOfStudy, int startYear, int endYear

### 11. Experience
- **Fields:** String company, String title, int startYear, int endYear

---

## Example Usage

```java
LinkedInService service = new LinkedInService();
User alice = new User(1, "Alice");
User bob = new User(2, "Bob");
service.registerUser(alice);
service.registerUser(bob);

alice.sendConnectionRequest(bob);
service.addConnection(alice, bob);

Profile profile = alice.getProfile();
profile.addSkill(new Skill("Java"));
profile.addEducation(new Education("MIT", "BSc", "CS", 2010, 2014));
profile.addExperience(new Experience("Google", "Software Engineer", 2014, 2018));

JobPosting job = new JobPosting(1, "Backend Developer", "Work on scalable systems", alice);
service.postJob(job);

service.sendMessage(alice, bob, "Hi Bob, let's connect!");
```

---

## Demo

See `LinkedInDemo.java` for a sample usage and simulation of the LinkedIn system.

---

## Extending the Framework

- **Add endorsements:** Allow users to endorse each other's skills.
- **Add recommendations:** Support written recommendations for users.
- **Add company pages:** Allow companies to create and manage their own pages.

---