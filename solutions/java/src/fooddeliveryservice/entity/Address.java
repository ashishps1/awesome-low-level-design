package fooddeliveryservice.entity;

public class Address {
    private String street;
    private String city;
    private String zipCode;
    private double latitude;
    private double longitude;

    public Address(String street, String city, String zipCode, double latitude, double longitude) {
        this.street = street;
        this.city = city;
        this.zipCode = zipCode;
        this.latitude = latitude;
        this.longitude = longitude;
    }

    public String getCity() {
        return city;
    }

    public double distanceTo(Address other) {
        double latDiff = this.latitude - other.latitude;
        double lonDiff = this.longitude - other.longitude;
        return Math.sqrt(latDiff * latDiff + lonDiff * lonDiff);
    }

    @Override
    public String toString() {
        return street + ", " + city + ", " + zipCode + " @(" + latitude + ", " + longitude + ")";
    }
}