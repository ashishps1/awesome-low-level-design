package restaurantmanagementsystem;

public class Staff {
    private final int id;
    private final String name;
    private final String role;
    private final String contactNumber;

    public Staff(int id, String name, String role, String contactNumber) {
        this.id = id;
        this.name = name;
        this.role = role;
        this.contactNumber = contactNumber;
    }
}
