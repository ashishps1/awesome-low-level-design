public class ObserverDemo {
    public static void main(String[] args) {
        WeatherStation weatherStation = new WeatherStation();

        TemperatureDisplay phoneDisplay = new TemperatureDisplay("Phone");
        TemperatureDisplay laptopDisplay = new TemperatureDisplay("Laptop");

        weatherStation.attach(phoneDisplay);
        weatherStation.attach(laptopDisplay);

        System.out.println("Weather station setting temperature to 25.0 degrees Celsius");
        weatherStation.setTemperature(25.0f);

        System.out.println("\nWeather station setting temperature to 30.5 degrees Celsius");
        weatherStation.setTemperature(30.5f);

        weatherStation.detach(laptopDisplay);

        System.out.println("\nWeather station setting temperature to 20.0 degrees Celsius");
        weatherStation.setTemperature(20.0f);
    }
}