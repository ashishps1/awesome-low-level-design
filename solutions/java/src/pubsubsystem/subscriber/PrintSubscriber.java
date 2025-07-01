package pubsubsystem.subscriber;

import pubsubsystem.Message;

public class PrintSubscriber implements Subscriber {
    private final String name;

    public PrintSubscriber(String name) {
        this.name = name;
    }

    @Override
    public void consume(Message message) {
        System.out.println("Subscriber " + name + " received message: " + message.getContent());
    }
}
