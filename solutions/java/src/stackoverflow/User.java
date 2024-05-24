package stackoverflow;

public class User {
    private final int id;
    private final String username;
    private final String password;
    private final String email;
    private int reputation;

    public User(int id, String username, String password, String email, int reputation) {
        this.id = id;
        this.username = username;
        this.password = password;
        this.email = email;
        this.reputation = reputation;
    }

    public void setReputation(int reputation) {
        this.reputation = reputation;
    }

    public int getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getEmail() {
        return email;
    }

    public int getReputation() {
        return reputation;
    }
}
