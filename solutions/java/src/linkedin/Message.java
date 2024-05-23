package linkedin;

import java.sql.Timestamp;

public class Message {
    private String id;
    private User sender;
    private User receiver;
    private String content;
    private Timestamp timestamp;

    public Message(String id, User sender, User receiver, String content, Timestamp timestamp) {
        this.id = id;
        this.sender = sender;
        this.receiver = receiver;
        this.content = content;
        this.timestamp = timestamp;
    }
}
