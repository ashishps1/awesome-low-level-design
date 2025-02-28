using System.Collections.Generic;

namespace StackOverflow
{
    public interface ICommentable
    {
        void AddComment(Comment comment);
        List<Comment> GetComments();
    }
}