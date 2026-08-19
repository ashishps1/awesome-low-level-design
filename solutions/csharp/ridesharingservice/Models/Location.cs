class Location(double latitude, double longitude)
{
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
