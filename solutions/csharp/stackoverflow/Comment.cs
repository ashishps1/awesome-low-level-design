using System;

namespace StackOverflow
{
    public class Comment
    {
        public int Id { get; }
        public string Content { get; }
        public User Author { get; }
        public DateTime CreationDate { get; }

        public Comment(User author, string content)
        {
            Id = GenerateId();
            Author = author;
            Content = content;
            CreationDate = DateTime.Now;
        }

        private int GenerateId()
        {
            return (int)(DateTime.Now.Ticks % int.MaxValue);
        }
    }
}