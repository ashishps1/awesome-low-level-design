using System.Collections.Concurrent;

class StackOverflowService
{
    private readonly ConcurrentDictionary<string, User> users = new ConcurrentDictionary<string, User>();
    private readonly ConcurrentDictionary<string, Question> questions = new ConcurrentDictionary<string, Question>();
    private readonly ConcurrentDictionary<string, Answer> answers = new ConcurrentDictionary<string, Answer>();
    private readonly IPostObserver reputationManager = new ReputationManager();

    public User CreateUser(string name)
    {
        User user = new User(name);
        users.TryAdd(user.GetId(), user);
        return user;
    }

    public Question PostQuestion(string userId, string title, string body, HashSet<Tag> tags)
    {
        User author = users[userId];
        Question question = new Question(title, body, author, tags);
        question.AddObserver(reputationManager);
        questions.TryAdd(question.GetId(), question);
        return question;
    }

    public Answer PostAnswer(string userId, string questionId, string body)
    {
        User author = users[userId];
        Question question = questions[questionId];
        Answer answer = new Answer(body, author);
        answer.AddObserver(reputationManager);
        question.AddAnswer(answer);
        answers.TryAdd(answer.GetId(), answer);
        return answer;
    }

    public void VoteOnPost(string userId, string postId, VoteType voteType)
    {
        User user = users[userId];
        Post post = FindPostById(postId);
        post.Vote(user, voteType);
    }

    public void AcceptAnswer(string questionId, string answerId)
    {
        Question question = questions[questionId];
        Answer answer = answers[answerId];
        question.AcceptAnswer(answer);
    }

    public List<Question> SearchQuestions(List<ISearchStrategy> strategies)
    {
        List<Question> results = questions.Values.ToList();

        foreach (var strategy in strategies)
        {
            results = strategy.Filter(results);
        }

        return results;
    }

    public User GetUser(string userId)
    {
        return users[userId];
    }

    private Post FindPostById(string postId)
    {
        if (questions.TryGetValue(postId, out Question question))
        {
            return question;
        }
        else if (answers.TryGetValue(postId, out Answer answer))
        {
            return answer;
        }

        throw new KeyNotFoundException("Post not found");
    }
}