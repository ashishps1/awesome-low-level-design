package linkedin.services;

import linkedin.entities.Member;
import linkedin.entities.NewsFeed;
import linkedin.entities.Post;
import linkedin.strategy.FeedSortingStrategy;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class NewsFeedService {
    private final Map<String, List<Post>> allPosts; // A map of memberId -> list of their posts

    public NewsFeedService() {
        this.allPosts = new ConcurrentHashMap<>();
    }

    public void addPost(Member member, Post post) {
        String memberId = member.getId();
        if(!allPosts.containsKey(memberId)) {
            allPosts.put(memberId, new ArrayList<>());
        }
        allPosts.get(memberId).add(post);
    }

    public List<Post> getMemberPosts(Member member) {
        return allPosts.getOrDefault(member.getId(), new ArrayList<>());
    }

    public void displayFeedForMember(Member member, FeedSortingStrategy feedSortingStrategy) {
        List<Post> feedPosts = new ArrayList<>();
        // Add posts from the member's connections
        for (Member connection : member.getConnections()) {
            List<Post> connectionPosts = allPosts.get(connection.getId());
            if (connectionPosts != null) {
                feedPosts.addAll(connectionPosts);
            }
        }

        NewsFeed feed = new NewsFeed(feedPosts);
        feed.display(feedSortingStrategy);
    }
}
