package pubsubsystem.subscriber;

import pubsubsystem.entities.Message;

public interface Subscriber {
    String getId();
    void onMessage(Message message);
}
