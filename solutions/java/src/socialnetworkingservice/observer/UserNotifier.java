package socialnetworkingservice.observer;

import socialnetworkingservice.model.Comment;
import socialnetworkingservice.model.Post;
import socialnetworkingservice.model.User;

public class UserNotifier implements PostObserver {
    @Override
    public void onPostCreated(Post post) {
        User author = post.getAuthor();
        for (User friend: author.getFriends()) {
            System.out.println("Notification for " + friend.getName() + ": " + author.getName() + " created a new post: " + post.getContent());
        }
    }

    @Override
    public void onLike(Post post, User user) {
        User author = post.getAuthor();
        System.out.println("Notification for " + author.getName() + ": " + user.getName() + " liked your post");
    }

    @Override
    public void onComment(Post post, Comment comment) {
        User author = post.getAuthor();
        System.out.println("Notification for " + author.getName() + ": " + comment.getAuthor().getName() + " commented on your post");
    }
}