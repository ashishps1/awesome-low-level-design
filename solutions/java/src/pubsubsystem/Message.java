package pubsubsystem;

public class Message {
    private final String payload;

    public Message(String payload) {
        this.payload = payload;
    }

    public String getPayload() {
        return payload;
    }
}
