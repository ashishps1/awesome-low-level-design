class ReputationManager : IPostObserver
{
    private const int QUESTION_UPVOTE_REP = 5;
    private const int ANSWER_UPVOTE_REP = 10;
    private const int ACCEPTED_ANSWER_REP = 15;
    private const int DOWNVOTE_REP_PENALTY = -1;
    private const int POST_DOWNVOTED_REP_PENALTY = -2;

    public void OnPostEvent(Event eventObj)
    {
        User postAuthor = eventObj.GetTargetPost().GetAuthor();

        switch (eventObj.GetEventType())
        {
            case EventType.UPVOTE_QUESTION:
                postAuthor.UpdateReputation(QUESTION_UPVOTE_REP);
                break;
            case EventType.DOWNVOTE_QUESTION:
                postAuthor.UpdateReputation(DOWNVOTE_REP_PENALTY);
                eventObj.GetActor().UpdateReputation(POST_DOWNVOTED_REP_PENALTY);
                break;
            case EventType.UPVOTE_ANSWER:
                postAuthor.UpdateReputation(ANSWER_UPVOTE_REP);
                break;
            case EventType.DOWNVOTE_ANSWER:
                postAuthor.UpdateReputation(DOWNVOTE_REP_PENALTY);
                eventObj.GetActor().UpdateReputation(POST_DOWNVOTED_REP_PENALTY);
                break;
            case EventType.ACCEPT_ANSWER:
                postAuthor.UpdateReputation(ACCEPTED_ANSWER_REP);
                break;
        }
    }
}