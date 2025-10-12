Facade Pattern: The SocialNetworkFacade is the main entry point for the client. It provides a simple, unified interface (createPost, addFriend, getNewsFeed) to the complex subsystem of services and repositories.

Observer Pattern: The PostService acts as a Subject. When a user creates a post, it notifies all registered Observers (like a NewsFeedNotifier). This decouples the action of posting from the consequence of updating news feeds.

Strategy Pattern: The NewsFeedService uses a NewsFeedGenerationStrategy to generate a user's news feed. The default is a ChronologicalStrategy, but this can be easily swapped for a more complex algorithm.

Composite Pattern: To model comments and replies, the Commentable interface is used. Both Post and Comment implement this interface, allowing them to be treated uniformly. A comment can be added to a post or to another comment, forming a tree structure.

Singleton Pattern: The Repository classes are implemented as Singletons to provide a global, in-memory data store for this simulation.

Repository Pattern: This pattern is used to abstract the data access layer. Services interact with UserRepository and PostRepository interfaces, completely decoupling them from the underlying data storage mechanism (which is a ConcurrentHashMap in this case).
