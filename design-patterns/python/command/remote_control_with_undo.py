from typing import Optional
from .command import Command


class RemoteControlWithUndo:
    """Invoker - Remote control with undo functionality"""
    
    def __init__(self):
        self._command: Optional[Command] = None
        self._last_command: Optional[Command] = None
    
    def set_command(self, command: Command) -> None:
        self._command = command
    
    def press_button(self) -> None:
        if self._command:
            self._command.execute()
            self._last_command = self._command
        else:
            print("No command set!")
    
    def press_undo(self) -> None:
        if self._last_command:
            self._last_command.undo()
            print("Command undone")
        else:
            print("No command to undo!")