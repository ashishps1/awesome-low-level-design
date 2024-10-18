using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace StackOverflow
{
    public class StackOverflowSystem
    {
        private readonly ConcurrentDictionary<int, User> _users;
        private readonly ConcurrentDictionary<int, Question> _questions;
        private readonly ConcurrentDictionary<int, Answer> _answers;
        private readonly ConcurrentDictionary<string, Tag> _tags;

        public StackOverflowSystem()
        {
            _users = new ConcurrentDictionary<int, User>();
            _questions = new ConcurrentDictionary<int, Question>();
            _answers = new ConcurrentDictionary<int, Answer>();
            _tags = new ConcurrentDictionary<string, Tag>();
        }

        public User CreateUser(string username, string email)
        {
            int id = _users.Count + 1;
            var user = new User(id, username, email);
            _users[id] = user;
            return user;
        }

        public Question AskQuestion(User user, string title, string content, List<string> tagNames)
        {
            var question = user.AskQuestion(title, content, tagNames);
            _questions[question.Id] = question;
            foreach (var tag in question.Tags)
            {
                _tags.TryAdd(tag.Name, tag);
            }
            return question;
        }

        public Answer AnswerQuestion(User user, Question question, string content)
        {
            var answer = user.AnswerQuestion(question, content);
            _answers[answer.Id] = answer;
            return answer;
        }

        public Comment AddComment(User user, ICommentable commentable, string content)
        {
            return user.AddComment(commentable, content);
        }

        public void VoteQuestion(User user, Question question, int value)
        {
            question.Vote(user, value);
        }

        public void VoteAnswer(User user, Answer answer, int value)
        {
            answer.Vote(user, value);
        }

        public void AcceptAnswer(Answer answer)
        {
            answer.MarkAsAccepted();
        }

        public List<Question> SearchQuestions(string query)
        {
            return _questions.Values
                .Where(q => q.Title.ToLower().Contains(query.ToLower()) ||
                            q.Content.ToLower().Contains(query.ToLower()) ||
                            q.Tags.Any(t => t.Name.ToLower().Equals(query.ToLower())))
                .ToList();
        }

        public List<Question> GetQuestionsByUser(User user)
        {
            return user.GetQuestions();
        }
    }
}