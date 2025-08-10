class Location
{
    private readonly double latitude;
    private readonly double longitude;

    public Location(double lat, double lng)
    {
        latitude = lat;
        longitude = lng;
    }

    public double DistanceTo(Location other)
    {
        double dx = latitude - other.latitude;
        double dy = longitude - other.longitude;
        return Math.Sqrt(dx * dx + dy * dy);
    }

    public double Latitude => latitude;
    public double Longitude => longitude;

    public override string ToString()
    {
        return $"Location({latitude}, {longitude})";
    }
}