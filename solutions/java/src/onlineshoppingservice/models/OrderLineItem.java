package onlineshoppingservice.models;

public class OrderLineItem {
    private final String productId;
    private final String productName;
    private final int quantity;
    private final double priceAtPurchase;

    public OrderLineItem(String productId, String productName, int quantity, double priceAtPurchase) {
        this.productId = productId;
        this.productName = productName;
        this.quantity = quantity;
        this.priceAtPurchase = priceAtPurchase;
    }

    public String getProductId() { return productId; }
    public int getQuantity() { return quantity; }
}
