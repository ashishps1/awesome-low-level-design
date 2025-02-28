namespace HotelManagement
{
    public class Guest
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public string PhoneNumber { get; }

        public Guest(string id, string name, string email, string phoneNumber)
        {
            Id = id;
            Name = name;
            Email = email;
            PhoneNumber = phoneNumber;
        }
    }
}