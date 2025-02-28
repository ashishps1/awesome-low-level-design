namespace CarRentalSystem
{
    public class Customer
    {
        public string Name { get; }
        public string ContactInfo { get; }
        public string DriversLicenseNumber { get; }

        public Customer(string name, string contactInfo, string driversLicenseNumber)
        {
            Name = name;
            ContactInfo = contactInfo;
            DriversLicenseNumber = driversLicenseNumber;
        }
    }
}