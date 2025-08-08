package pubsubsystem.entities;

import java.time.Instant;

public class Message {
    private final String payload;
    private final Instant timestamp;

    public Message(String payload) {
        this.payload = payload;
        this.timestamp = Instant.now();
    }

    public String getPayload() {
        return payload;
    }

    @Override
    public String toString() {
        return "Message{" + "payload='" + payload + '\'' + '}';
    }
}
