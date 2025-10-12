class Vehicle
{
    private readonly string licenseNumber;
    private readonly string model;
    private readonly RideType type;

    public Vehicle(string license, string m, RideType t)
    {
        licenseNumber = license;
        model = m;
        type = t;
    }

    public string LicenseNumber => licenseNumber;
    public string Model => model;
    public RideType Type => type;
}