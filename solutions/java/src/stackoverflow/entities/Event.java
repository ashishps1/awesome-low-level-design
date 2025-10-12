package stackoverflow.entities;

import stackoverflow.enums.EventType;

public class Event {
    private final EventType type;
    private final User actor;        // user who performed the action
    private final Post targetPost;   // post being acted on

    public Event(EventType type, User actor, Post targetPost) {
        this.type = type;
        this.actor = actor;
        this.targetPost = targetPost;
    }

    public EventType getType() { return type; }
    public User getActor() { return actor; }
    public Post getTargetPost() { return targetPost; }
}
