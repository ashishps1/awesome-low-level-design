package linkedin;

import java.util.List;

public class User {
    private String id;
    private String name;
    private String email;
    private String password;
    private Profile profile;
    private List<Connection> connections;
    private List<Message> inbox;
    private List<Message> sentMessages;

    public User(String id, String name, String email, String password, Profile profile, List<Connection> connections, List<Message> inbox, List<Message> sentMessages) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.password = password;
        this.profile = profile;
        this.connections = connections;
        this.inbox = inbox;
        this.sentMessages = sentMessages;
    }

    public void setProfile(Profile profile) {
        this.profile = profile;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public Profile getProfile() {
        return profile;
    }

    public List<Connection> getConnections() {
        return connections;
    }

    public List<Message> getInbox() {
        return inbox;
    }

    public List<Message> getSentMessages() {
        return sentMessages;
    }
}
