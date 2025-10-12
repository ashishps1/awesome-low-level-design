class Post : CommentableEntity
{
    public Post(User author, string content) : base(author, content) { }
}