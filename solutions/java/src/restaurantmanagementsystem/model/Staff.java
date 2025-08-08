package restaurantmanagementsystem.model;

public abstract class Staff {
    protected String id;
    protected String name;

    public Staff(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() { return id; }
    public String getName() { return name; }
}