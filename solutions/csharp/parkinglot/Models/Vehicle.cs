abstract class Vehicle
{
    protected readonly string licenseNumber;
    protected readonly VehicleSize size;

    public Vehicle(string licenseNumber, VehicleSize size)
    {
        this.licenseNumber = licenseNumber;
        this.size = size;
    }

    public string GetLicenseNumber()
    {
        return licenseNumber;
    }

    public VehicleSize GetSize()
    {
        return size;
    }
}

class Bike : Vehicle
{
    public Bike(string licenseNumber) : base(licenseNumber, VehicleSize.SMALL)
    {
    }
}

class Car : Vehicle
{
    public Car(string licenseNumber) : base(licenseNumber, VehicleSize.MEDIUM)
    {
    }
}

class Truck : Vehicle
{
    public Truck(string licenseNumber) : base(licenseNumber, VehicleSize.LARGE)
    {
    }
}