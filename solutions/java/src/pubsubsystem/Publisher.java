package pubsubsystem;

public class Publisher {
    private final Topic topic;

    public Publisher(Topic topic) {
        this.topic = topic;
    }

    public void publish(Message message) {
        topic.publish(message);
    }
}
