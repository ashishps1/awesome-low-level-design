namespace TrafficSignalSystem
{
    public class Road
    {
        public string Id { get; }
        public string Name { get; }
        public TrafficLight TrafficLight { get; private set; }

        public Road(string id, string name)
        {
            Id = id;
            Name = name;
        }

        public void SetTrafficLight(TrafficLight trafficLight)
        {
            TrafficLight = trafficLight;
        }
    }
}