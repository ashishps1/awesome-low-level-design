package linkedin;

import java.util.Date;
import java.util.UUID;

public class Message {
    private final String id;
    private final User sender;
    private final User receiver;
    private final String content;
    private final Date timestamp;

    public Message(User sender, User receiver, String content) {
        this.id = UUID.randomUUID().toString();
        this.sender = sender;
        this.receiver = receiver;
        this.content = content;
        this.timestamp = new Date();
    }
}
