package trafficsignalsystem;

public class TrafficSignalSystemDemo {
    public static void run() {
        TrafficController trafficController = TrafficController.getInstance();

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
        road1.setTrafficLight(trafficLight1);
        road2.setTrafficLight(trafficLight2);
        road3.setTrafficLight(trafficLight3);
        road4.setTrafficLight(trafficLight4);

        // Add roads to the traffic controller
        trafficController.addRoad(road1);
        trafficController.addRoad(road2);
        trafficController.addRoad(road3);
        trafficController.addRoad(road4);

        // Start traffic control
        trafficController.startTrafficControl();

        // Simulate an emergency on a specific road
        trafficController.handleEmergency("R2");
    }
}
