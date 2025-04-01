namespace FoodDeliveryService
{
    public class DeliveryAgent
    {
        public string Id { get; }
        public string Name { get; }
        public string Phone { get; }
        public bool Available { get; private set; }

        public DeliveryAgent(string id, string name, string phone)
        {
            Id = id;
            Name = name;
            Phone = phone;
            Available = true;
        }

        public void SetAvailable(bool available)
        {
            Available = available;
        }
    }
}