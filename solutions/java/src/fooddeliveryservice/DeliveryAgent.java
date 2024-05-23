package fooddeliveryservice;

public class DeliveryAgent {
    private final String id;
    private final String name;
    private final String phone;
    private boolean available;

    public DeliveryAgent(String id, String name, String phone) {
        this.id = id;
        this.name = name;
        this.phone = phone;
        this.available = true;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public String getId() {
        return id;
    }

    public boolean isAvailable() {
        return available;
    }
}
