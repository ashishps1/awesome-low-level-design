class Event
{
    private readonly EventType type;
    private readonly User actor;
    private readonly Post targetPost;

    public Event(EventType type, User actor, Post targetPost)
    {
        this.type = type;
        this.actor = actor;
        this.targetPost = targetPost;
    }

    public EventType GetEventType() { return type; }
    public User GetActor() { return actor; }
    public Post GetTargetPost() { return targetPost; }
}