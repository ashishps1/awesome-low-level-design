package pubsubsystem.subscriber;

import pubsubsystem.Message;

public interface Subscriber {
    void consume(Message message);
}
