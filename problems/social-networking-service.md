# Designing a Social Network Like Facebook

## Requirements
#### User Registration and Authentication:
- Users should be able to create an account with their personal information, such as name, email, and password.
- Users should be able to log in and log out of their accounts securely.
#### User Profiles:
- Each user should have a profile with their information, such as profile picture, bio, and interests.
- Users should be able to update their profile information.
#### Friend Connections:
- Users should be able to send friend requests to other users.
- Users should be able to accept or decline friend requests.
- Users should be able to view their list of friends.
#### Posts and Newsfeed:
- Users should be able to create posts with text, images, or videos.
- Users should be able to view a newsfeed consisting of posts from their friends and their own posts.
- The newsfeed should be sorted in reverse chronological order.
#### Likes and Comments:
- Users should be able to like and comment on posts.
- Users should be able to view the list of likes and comments on a post.
#### Privacy and Security:
- Users should be able to control the visibility of their posts and profile information.
- The system should enforce secure access control to ensure data privacy.
#### Notifications:
- Users should receive notifications for events such as friend requests, likes, comments, and mentions.
- Notifications should be delivered in real-time.
#### Scalability and Performance:
- The system should be designed to handle a large number of concurrent users and high traffic load.
- The system should be scalable and efficient in terms of resource utilization.

## Implementations
#### [Java Implementation](../solutions/java/src/socialnetworkingservice/) 
#### [Python Implementation](../solutions/python/socialnetworkingservice/)

## Classes, Interfaces and Enumerations
1. The **User** class represents a user in the social networking system, containing properties such as ID, name, email, password, profile picture, bio, list of friends, and list of posts.
2. The **Post** class represents a post created by a user, containing properties such as ID, user ID, content, image URLs, video URLs, timestamp, likes, and comments.
3. The **Comment** class represents a comment made by a user on a post, containing properties such as ID, user ID, post ID, content, and timestamp.
4. The **Notification** class represents a notification generated for a user, containing properties such as ID, user ID, notification type, content, and timestamp.
5. The **NotificationType** enum defines the different types of notifications, such as friend request, friend request accepted, like, comment, and mention.
6. The **SocialNetworkingService** class is the main class that manages the social networking system. It follows the Singleton pattern to ensure only one instance of the service exists.
7. The SocialNetworkingService class provides methods for user registration, login, profile updates, friend requests, post creation, newsfeed generation, likes, comments, and notifications.
8. Multi-threading is achieved using concurrent data structures such as ConcurrentHashMap and CopyOnWriteArrayList to handle concurrent access to shared resources.
9. The **SocialNetworkingDemo** class demonstrates the usage of the social networking system by registering users, logging in, sending friend requests, creating posts, liking posts, commenting on posts, and retrieving newsfeed and notifications.