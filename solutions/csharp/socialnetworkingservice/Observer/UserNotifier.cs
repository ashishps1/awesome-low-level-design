class UserNotifier : IPostObserver
{
    public void OnPostCreated(Post post)
    {
        User author = post.GetAuthor();
        foreach (User friend in author.GetFriends())
        {
            Console.WriteLine($"Notification for {friend.GetName()}: {author.GetName()} created a new post: {post.GetContent()}");
        }
    }

    public void OnLike(Post post, User user)
    {
        User author = post.GetAuthor();
        Console.WriteLine($"Notification for {author.GetName()}: {user.GetName()} liked your post");
    }

    public void OnComment(Post post, Comment comment)
    {
        User author = post.GetAuthor();
        Console.WriteLine($"Notification for {author.GetName()}: {comment.GetAuthor().GetName()} commented on your post");
    }
}