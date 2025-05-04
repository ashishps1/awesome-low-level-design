package pubsubsystem;

public interface Subscriber {
    void consume(Message message);
}
