using System;
using System.Collections.Generic;
using System.Linq;

namespace StackOverflow
{
    public class Answer : IVotable, ICommentable
    {
        public int Id { get; }
        public string Content { get; }
        public User Author { get; }
        public Question Question { get; }
        public bool IsAccepted { get; private set; }
        public DateTime CreationDate { get; }
        private readonly List<Comment> _comments;
        private readonly List<Vote> _votes;

        public Answer(User author, Question question, string content)
        {
            Id = GenerateId();
            Author = author;
            Question = question;
            Content = content;
            CreationDate = DateTime.Now;
            _votes = new List<Vote>();
            _comments = new List<Comment>();
            IsAccepted = false;
        }

        public void Vote(User user, int value)
        {
            if (value != 1 && value != -1)
            {
                throw new ArgumentException("Vote value must be either 1 or -1");
            }
            _votes.RemoveAll(v => v.User.Equals(user));
            _votes.Add(new Vote(user, value));
            Author.UpdateReputation(value * 10);
        }

        public int GetVoteCount()
        {
            return _votes.Sum(v => v.Value);
        }

        public void AddComment(Comment comment)
        {
            _comments.Add(comment);
        }

        public List<Comment> GetComments()
        {
            return new List<Comment>(_comments);
        }

        public void MarkAsAccepted()
        {
            if (IsAccepted)
            {
                throw new InvalidOperationException("This answer is already accepted");
            }
            IsAccepted = true;
            Author.UpdateReputation(15);
        }

        private int GenerateId()
        {
            return (int)(DateTime.Now.Ticks % int.MaxValue);
        }
    }
}