package socialnetworkingservice.observer;

import socialnetworkingservice.model.Comment;
import socialnetworkingservice.model.Post;
import socialnetworkingservice.model.User;

public interface PostObserver {
    void onPostCreated(Post post);
    void onLike(Post post, User user);
    void onComment(Post post, Comment comment);
}