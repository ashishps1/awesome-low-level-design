package linkedin.entities;

import linkedin.strategy.FeedSortingStrategy;

import java.util.List;

public class NewsFeed {
    private final List<Post> posts;

    public NewsFeed(List<Post> posts) {
        this.posts = posts;
    }

    public void display(FeedSortingStrategy strategy) {
        List<Post> sortedPosts = strategy.sort(posts);
        if (sortedPosts.isEmpty()) {
            System.out.println("  Your news feed is empty.");
            return;
        }
        sortedPosts.forEach(post -> {
            System.out.println("----------------------------------------");
            System.out.printf("Post by: %s (at %s)%n", post.getAuthor().getName(), post.getCreatedAt().toLocalDate());
            System.out.println("Content: " + post.getContent());
            System.out.printf("Likes: %d, Comments: %d%n", post.getLikes().size(), post.getComments().size());
            System.out.println("----------------------------------------");
        });
    }
}
