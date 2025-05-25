public class CommandPatternDemo {
    public static void main(String[] args) {
        // Receivers
        Light light = new Light();
        Thermostat thermostat = new Thermostat();

        // Commands
        Command lightOn = new LightOnCommand(light);
        Command lightOff = new LightOffCommand(light);
        Command setTemp22 = new SetTemperatureCommand(thermostat, 22);

        // Invoker
        SmartButton button = new SmartButton();

        // Simulate usage
        System.out.println("→ Pressing Light ON");
        button.setCommand(lightOn);
        button.press();

        System.out.println("→ Pressing Set Temp to 22°C");
        button.setCommand(setTemp22);
        button.press();

        System.out.println("→ Pressing Light OFF");
        button.setCommand(lightOff);
        button.press();

        System.out.println("\n🔁 Undo Last Action");
        button.undoLast(); // Undo Light OFF

        System.out.println("🔁 Undo Previous Action");
        button.undoLast(); // Undo Set Temp

        System.out.println("🔁 Undo Again");
        button.undoLast(); // Undo Light ON

        System.out.println("🔁 Undo Once More");
        button.undoLast(); // No more actions
    }
}