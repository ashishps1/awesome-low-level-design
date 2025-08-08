package socialnetworkingservice.strategy;

import socialnetworkingservice.model.Post;
import socialnetworkingservice.model.User;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class ChronologicalStrategy implements NewsFeedGenerationStrategy {
    @Override
    public List<Post> generateFeed(User user) {
        Set<User> friends = user.getFriends();
        List<Post> feed = new ArrayList<>();

        for (User friend: friends) {
            feed.addAll(friend.getPosts());
        }

        // Sort posts by timestamp in reverse (most recent first)
        feed.sort((p1, p2) -> p2.getTimestamp().compareTo(p1.getTimestamp()));

        return feed;
    }
}
