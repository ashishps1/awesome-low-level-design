using System;
using System.Collections.Generic;
using System.Threading;

namespace TrafficSignalSystem
{
    public class TrafficController
    {
        private static TrafficController _instance;
        private readonly Dictionary<string, Road> _roads;

        private TrafficController()
        {
            _roads = new Dictionary<string, Road>();
        }

        public static TrafficController GetInstance()
        {
            if (_instance == null)
            {
                _instance = new TrafficController();
            }
            return _instance;
        }

        public void AddRoad(Road road)
        {
            _roads[road.Id] = road;
        }

        public void RemoveRoad(string roadId)
        {
            _roads.Remove(roadId);
        }

        public void StartTrafficControl()
        {
            foreach (var road in _roads.Values)
            {
                TrafficLight trafficLight = road.TrafficLight;
                new Thread(() =>
                {
                    while (true)
                    {
                        try
                        {
                            Thread.Sleep(trafficLight.RedDuration);
                            trafficLight.ChangeSignal(Signal.GREEN);
                            Thread.Sleep(trafficLight.GreenDuration);
                            trafficLight.ChangeSignal(Signal.YELLOW);
                            Thread.Sleep(trafficLight.YellowDuration);
                            trafficLight.ChangeSignal(Signal.RED);
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                    }
                }).Start();
            }
        }

        public void HandleEmergency(string roadId)
        {
            if (_roads.ContainsKey(roadId))
            {
                TrafficLight trafficLight = _roads[roadId].TrafficLight;
                trafficLight.ChangeSignal(Signal.GREEN);
                // Perform emergency handling logic
            }
        }
    }
}