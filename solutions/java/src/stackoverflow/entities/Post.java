package stackoverflow.entities;

import stackoverflow.enums.EventType;
import stackoverflow.enums.VoteType;
import stackoverflow.observer.PostObserver;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public abstract class Post extends Content {
    private final AtomicInteger voteCount = new AtomicInteger(0);
    private final Map<String, VoteType> voters = new ConcurrentHashMap<>();
    private final List<Comment> comments = new CopyOnWriteArrayList<>();
    private final List<PostObserver> observers = new CopyOnWriteArrayList<>();

    public Post(String id, String body, User author) {
        super(id, body, author);
    }

    public void addObserver(PostObserver observer) {
        this.observers.add(observer);
    }

    protected void notifyObservers(Event event) {
        observers.forEach(o -> o.onPostEvent(event));
    }

    public synchronized void vote(User user, VoteType voteType) {
        String userId = user.getId();
        if (voters.get(userId) == voteType)
            return; // Already voted

        int scoreChange = 0;
        if (voters.containsKey(userId)) { // User is changing their vote
            scoreChange = (voteType == VoteType.UPVOTE) ? 2 : -2;
        } else { // New vote
            scoreChange = (voteType == VoteType.UPVOTE) ? 1 : -1;
        }

        voters.put(userId, voteType);
        voteCount.addAndGet(scoreChange);

        EventType eventType = EventType.UPVOTE_QUESTION;

        if (this instanceof Question) {
            eventType = (voteType == VoteType.UPVOTE ? EventType.UPVOTE_QUESTION : EventType.DOWNVOTE_QUESTION);
        } else {
            eventType = (voteType == VoteType.UPVOTE ? EventType.UPVOTE_ANSWER : EventType.DOWNVOTE_ANSWER);
        }

        notifyObservers(new Event(eventType, user, this));
    }
}
