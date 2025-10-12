class Comment : CommentableEntity
{
    public Comment(User author, string content) : base(author, content) { }

    public List<Comment> GetReplies()
    {
        return GetComments();
    }
}