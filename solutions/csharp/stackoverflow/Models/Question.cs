class Question : Post
{
    private readonly string title;
    private readonly HashSet<Tag> tags;
    private readonly List<Answer> answers = new List<Answer>();
    private Answer acceptedAnswer;

    public Question(string title, string body, User author, HashSet<Tag> tags)
        : base(Guid.NewGuid().ToString(), body, author)
    {
        this.title = title;
        this.tags = tags;
    }

    public void AddAnswer(Answer answer)
    {
        answers.Add(answer);
    }

    public void AcceptAnswer(Answer answer)
    {
        lock (this)
        {
            if (!author.GetId().Equals(answer.GetAuthor().GetId()) && acceptedAnswer == null)
            {
                acceptedAnswer = answer;
                answer.SetAccepted(true);
                NotifyObservers(new Event(EventType.ACCEPT_ANSWER, answer.GetAuthor(), answer));
            }
        }
    }

    public string GetTitle() { return title; }
    public HashSet<Tag> GetTags() { return tags; }
    public List<Answer> GetAnswers() { return answers; }
}