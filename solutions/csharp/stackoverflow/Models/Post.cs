using System.Collections.Concurrent;

abstract class Post : Content
{
    private int voteCount = 0;
    private readonly ConcurrentDictionary<string, VoteType> voters = new ConcurrentDictionary<string, VoteType>();
    private readonly List<Comment> comments = new List<Comment>();
    private readonly List<IPostObserver> observers = new List<IPostObserver>();
    private readonly object postLock = new object();

    public Post(string id, string body, User author) : base(id, body, author)
    {
    }

    public void AddObserver(IPostObserver observer)
    {
        observers.Add(observer);
    }

    protected void NotifyObservers(Event eventObj)
    {
        foreach (var observer in observers)
        {
            observer.OnPostEvent(eventObj);
        }
    }

    public void Vote(User user, VoteType voteType)
    {
        lock (postLock)
        {
            string userId = user.GetId();
            if (voters.TryGetValue(userId, out VoteType existingVote) && existingVote == voteType)
                return; // Already voted

            int scoreChange = 0;
            if (voters.ContainsKey(userId)) // User is changing their vote
            {
                scoreChange = (voteType == VoteType.UPVOTE) ? 2 : -2;
            }
            else // New vote
            {
                scoreChange = (voteType == VoteType.UPVOTE) ? 1 : -1;
            }

            voters[userId] = voteType;
            voteCount += scoreChange;

            EventType eventType;
            if (this is Question)
            {
                eventType = (voteType == VoteType.UPVOTE) ? EventType.UPVOTE_QUESTION : EventType.DOWNVOTE_QUESTION;
            }
            else
            {
                eventType = (voteType == VoteType.UPVOTE) ? EventType.UPVOTE_ANSWER : EventType.DOWNVOTE_ANSWER;
            }

            NotifyObservers(new Event(eventType, user, this));
        }
    }
}