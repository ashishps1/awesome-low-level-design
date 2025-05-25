public class Thermostat {
    private int currentTemperature = 20; // default

    public void setTemperature(int temp) {
        System.out.println("Thermostat set to " + temp + "°C");
        currentTemperature = temp;
    }

    public int getCurrentTemperature() {
        return currentTemperature;
    }
}