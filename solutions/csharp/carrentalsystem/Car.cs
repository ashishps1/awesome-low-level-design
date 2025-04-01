namespace CarRentalSystem
{
    public class Car
    {
        public string Make { get; }
        public string Model { get; }
        public int Year { get; }
        public string LicensePlate { get; }
        public double RentalPricePerDay { get; }
        public bool Available { get; private set; }

        public Car(string make, string model, int year, string licensePlate, double rentalPricePerDay)
        {
            Make = make;
            Model = model;
            Year = year;
            LicensePlate = licensePlate;
            RentalPricePerDay = rentalPricePerDay;
            Available = true;
        }

        public void SetAvailable(bool available)
        {
            Available = available;
        }
    }
}