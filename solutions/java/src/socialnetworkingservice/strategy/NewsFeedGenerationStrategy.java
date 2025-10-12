package socialnetworkingservice.strategy;

import socialnetworkingservice.model.Post;
import socialnetworkingservice.model.User;

import java.util.List;

public interface NewsFeedGenerationStrategy {
    List<Post> generateFeed(User user);
}
