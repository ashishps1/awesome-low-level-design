package votingsystem;

class Voter {
    private final String id;
    private final String name;
    private final String password;

    public Voter(String id, String name, String password) {
        this.id = id;
        this.name = name;
        this.password = password;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}