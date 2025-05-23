from .light import Light
from .light_on_command import LightOnCommand
from .light_off_command import LightOffCommand
from .remote_control import RemoteControl
from .remote_control_with_undo import RemoteControlWithUndo


def command_pattern_demo():
    """Demonstrate Command pattern"""
    print("=== Command Pattern Demo ===")
    
    # Create receivers
    living_room_light = Light("Living Room")
    bedroom_light = Light("Bedroom")
    
    # Create commands
    living_room_on = LightOnCommand(living_room_light)
    living_room_off = LightOffCommand(living_room_light)
    bedroom_on = LightOnCommand(bedroom_light)
    bedroom_off = LightOffCommand(bedroom_light)
    
    # Simple remote control demo
    print("\n--- Simple Remote Control ---")
    remote = RemoteControl()
    
    remote.set_command(living_room_on)
    remote.press_button()
    
    remote.set_command(living_room_off)
    remote.press_button()
    
    remote.set_command(bedroom_on)
    remote.press_button()
    
    # Remote control with undo demo
    print("\n--- Remote Control with Undo ---")
    undo_remote = RemoteControlWithUndo()
    
    undo_remote.set_command(bedroom_on)
    undo_remote.press_button()
    
    undo_remote.press_undo()  # Should turn off the light
    
    undo_remote.set_command(bedroom_off)
    undo_remote.press_button()
    
    undo_remote.press_undo()  # Should turn on the light
    
    # Demonstrate command switching
    print("\n--- Command Switching ---")
    undo_remote.set_command(living_room_on)
    undo_remote.press_button()
    
    undo_remote.set_command(bedroom_off)
    undo_remote.press_button()
    
    undo_remote.press_undo()  # Should undo bedroom off (turn on bedroom)


if __name__ == "__main__":
    command_pattern_demo()