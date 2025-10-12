package socialnetworkingservice.repository;

import socialnetworkingservice.model.Post;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class PostRepository {
    private static final PostRepository INSTANCE = new PostRepository();
    private final Map<String, Post> posts = new ConcurrentHashMap<>();

    private PostRepository() {}

    public static PostRepository getInstance() { return INSTANCE; }

    public void save(Post post) {
        posts.put(post.getId(), post);
    }

    public Post findById(String id) {
        return posts.get(id);
    }
}
