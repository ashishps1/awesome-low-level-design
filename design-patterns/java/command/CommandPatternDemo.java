public class CommandPatternDemo {
    public static void main(String[] args) {
        // Set up the receiver
        Light livingRoomLight = new Light("Living Room");
        Light kitchenLight = new Light("Kitchen");

        // Create concrete commands
        Command livingRoomLightOn = new LightOnCommand(livingRoomLight);
        Command livingRoomLightOff = new LightOffCommand(livingRoomLight);
        Command kitchenLightOn = new LightOnCommand(kitchenLight);
        Command kitchenLightOff = new LightOffCommand(kitchenLight);

        // Set up the invoker
        RemoteControl remote = new RemoteControl();

        // Use the invoker to execute commands
        remote.setCommand(livingRoomLightOn);
        remote.pressButton();
        remote.setCommand(kitchenLightOn);
        remote.pressButton();
        remote.setCommand(livingRoomLightOff);
        remote.pressButton();
        remote.setCommand(kitchenLightOff);
        remote.pressButton();

        // Demonstrate undo
        System.out.println("\nDemonstrating undo:");
        remote.setCommand(livingRoomLightOn);
        remote.pressButton();
        remote.pressUndoButton();

        // Demonstrate RemoteControlWithUndo
        System.out.println("\nDemonstrating RemoteControlWithUndo:");
        RemoteControlWithUndo advancedRemote = new RemoteControlWithUndo();
        advancedRemote.addCommand(livingRoomLightOn);
        advancedRemote.addCommand(kitchenLightOn);
        advancedRemote.executeCommands();
        advancedRemote.undoLastCommand();
        advancedRemote.undoLastCommand();
    }
}