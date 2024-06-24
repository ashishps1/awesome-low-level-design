class TemperatureDisplay implements Observer {
    private String name;

    public TemperatureDisplay(String name) {
        this.name = name;
    }

    @Override
    public void update(float temperature) {
        System.out.println(name + " displays Temperature: " + temperature + " degrees Celsius");
    }
}
