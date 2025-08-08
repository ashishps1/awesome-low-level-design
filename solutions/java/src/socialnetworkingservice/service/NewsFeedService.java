package socialnetworkingservice.service;

import socialnetworkingservice.model.Post;
import socialnetworkingservice.model.User;
import socialnetworkingservice.strategy.ChronologicalStrategy;
import socialnetworkingservice.strategy.NewsFeedGenerationStrategy;

import java.util.List;

public class NewsFeedService {
    private NewsFeedGenerationStrategy strategy;

    public NewsFeedService() {
        this.strategy = new ChronologicalStrategy(); // Default strategy
    }

    public void setStrategy(NewsFeedGenerationStrategy strategy) {
        this.strategy = strategy;
    }

    public List<Post> getNewsFeed(User user) {
        return strategy.generateFeed(user);
    }
}