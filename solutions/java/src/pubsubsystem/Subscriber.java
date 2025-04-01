package pubsubsystem;

public interface Subscriber {
    void onMessage(Message message);
}
