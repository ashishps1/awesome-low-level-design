package trafficsignalsystem;

public class Road {
    private final String id;
    private final String name;
    private TrafficLight trafficLight;

    public Road(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public void setTrafficLight(TrafficLight trafficLight) {
        this.trafficLight = trafficLight;
    }

    public TrafficLight getTrafficLight() {
        return trafficLight;
    }

    public String getId() {
        return id;
    }
}
