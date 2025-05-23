from typing import Optional
from .command import Command


class RemoteControl:
    """Invoker - Simple remote control"""
    
    def __init__(self):
        self._command: Optional[Command] = None
    
    def set_command(self, command: Command) -> None:
        self._command = command
    
    def press_button(self) -> None:
        if self._command:
            self._command.execute()
        else:
            print("No command set!")