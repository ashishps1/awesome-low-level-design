package restaurantmanagementsystem;

public class Table {
    private final int id;
    private final int capacity;
    private boolean isReserved = false;

    public Table(int id, int capacity) {
        this.id = id;
        this.capacity = capacity;
    }

    public synchronized void reserve() {
        if (isReserved) throw new IllegalStateException("Table already reserved");
        isReserved = true;
    }

    public synchronized void release() {
        isReserved = false;
    }

    public synchronized boolean isAvailable() {
        return !isReserved;
    }

    public int getId() { return id; }
}
