using System;

namespace TrafficSignalSystem
{
    public class TrafficLight
    {
        public string Id { get; }
        public Signal CurrentSignal { get; private set; }
        public int RedDuration { get; set; }
        public int YellowDuration { get; set; }
        public int GreenDuration { get; set; }

        public TrafficLight(string id, int redDuration, int yellowDuration, int greenDuration)
        {
            Id = id;
            RedDuration = redDuration;
            YellowDuration = yellowDuration;
            GreenDuration = greenDuration;
            CurrentSignal = Signal.RED;
        }

        public void ChangeSignal(Signal newSignal)
        {
            CurrentSignal = newSignal;
            NotifyObservers();
        }

        private void NotifyObservers()
        {
            // Notify observers (e.g., roads) about the signal change
            Console.WriteLine($"Traffic light {Id} changed to {CurrentSignal}");
        }
    }
}