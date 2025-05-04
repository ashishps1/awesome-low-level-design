package pubsubsystem;

public class LoggingSubscriber implements Subscriber {
    private final String name;

    public LoggingSubscriber(String name) {
        this.name = name;
    }

    @Override
    public void consume(Message message) {
        System.out.println("[LOG] " + name + " received: " + message.getPayload());
    }
}