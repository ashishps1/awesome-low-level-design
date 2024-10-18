using System;
using System.Collections.Generic;
using System.Linq;

namespace StackOverflow
{
    public class Question : IVotable, ICommentable
    {
        public int Id { get; }
        public string Title { get; }
        public string Content { get; }
        public User Author { get; }
        public DateTime CreationDate { get; }
        public List<Tag> Tags { get; }
        private readonly List<Answer> _answers;
        private readonly List<Comment> _comments;
        private readonly List<Vote> _votes;

        public Question(User author, string title, string content, List<string> tagNames)
        {
            Id = GenerateId();
            Author = author;
            Title = title;
            Content = content;
            CreationDate = DateTime.Now;
            _answers = new List<Answer>();
            _comments = new List<Comment>();
            _votes = new List<Vote>();
            Tags = tagNames.Select(tag => new Tag(tag)).ToList();
        }

        public void AddAnswer(Answer answer)
        {
            if (!_answers.Contains(answer))
            {
                _answers.Add(answer);
            }
        }

        public void Vote(User user, int value)
        {
            if (value != 1 && value != -1)
            {
                throw new ArgumentException("Vote value must be either 1 or -1");
            }
            _votes.RemoveAll(v => v.User.Equals(user));
            _votes.Add(new Vote(user, value));
            Author.UpdateReputation(value * 5);
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

        private int GenerateId()
        {
            return (int)(DateTime.Now.Ticks % int.MaxValue);
        }
    }
}