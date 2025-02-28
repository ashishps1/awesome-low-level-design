namespace ElevatorSystem
{
    public class Request
    {
        public int SourceFloor { get; }
        public int DestinationFloor { get; }

        public Request(int sourceFloor, int destinationFloor)
        {
            SourceFloor = sourceFloor;
            DestinationFloor = destinationFloor;
        }
    }
}