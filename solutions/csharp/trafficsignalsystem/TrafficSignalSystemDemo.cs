using System;

namespace TrafficSignalSystem
{
    public class TrafficSignalSystemDemo
    {
        public static void Run()
        {
            TrafficController trafficController = TrafficController.GetInstance();

            // Create roads
            Road road1 = new Road("R1", "Main Street");
            Road road2 = new Road("R2", "Broadway");
            Road road3 = new Road("R3", "Park Avenue");
            Road road4 = new Road("R4", "Elm Street");

            // Create traffic lights
            TrafficLight trafficLight1 = new TrafficLight("TL1", 6000, 3000, 9000);
            TrafficLight trafficLight2 = new TrafficLight("TL2", 6000, 3000, 9000);
            TrafficLight trafficLight3 = new TrafficLight("TL3", 6000, 3000, 9000);
            TrafficLight trafficLight4 = new TrafficLight("TL4", 6000, 3000, 9000);

            // Assign traffic lights to roads
            road1.SetTrafficLight(trafficLight1);
            road2.SetTrafficLight(trafficLight2);
            road3.SetTrafficLight(trafficLight3);
            road4.SetTrafficLight(trafficLight4);

            // Add roads to the traffic controller
            trafficController.AddRoad(road1);
            trafficController.AddRoad(road2);
            trafficController.AddRoad(road3);
            trafficController.AddRoad(road4);

            // Start traffic control
            trafficController.StartTrafficControl();

            // Simulate an emergency on a specific road
            trafficController.HandleEmergency("R2");
        }
    }
}