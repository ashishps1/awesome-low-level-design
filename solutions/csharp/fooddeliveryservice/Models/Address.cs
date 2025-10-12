class Address
{
    private readonly string street;
    private readonly string city;
    private readonly string zipCode;
    private readonly double latitude;
    private readonly double longitude;

    public Address(string street, string city, string zipCode, double latitude, double longitude)
    {
        this.street = street;
        this.city = city;
        this.zipCode = zipCode;
        this.latitude = latitude;
        this.longitude = longitude;
    }

    public string GetCity()
    {
        return city;
    }

    public double DistanceTo(Address other)
    {
        double latDiff = latitude - other.latitude;
        double lonDiff = longitude - other.longitude;
        return Math.Sqrt(latDiff * latDiff + lonDiff * lonDiff);
    }

    public override string ToString()
    {
        return $"{street}, {city}, {zipCode} @({latitude}, {longitude})";
    }
}