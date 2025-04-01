package votingsystem;

class Candidate {
    private final String id;
    private final String name;
    private final String party;

    public Candidate(String id, String name, String party) {
        this.id = id;
        this.name = name;
        this.party = party;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}