interface IPostObserver
{
    void OnPostCreated(Post post);
    void OnLike(Post post, User user);
    void OnComment(Post post, Comment comment);
}