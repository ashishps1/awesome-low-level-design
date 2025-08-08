package linkedin.strategy;

import linkedin.entities.Post;

import java.util.List;

public interface FeedSortingStrategy {
    List<Post> sort(List<Post> posts);
}
