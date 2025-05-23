from .command import Command
from .light import Light


class LightOnCommand(Command):
    """Concrete Command - Turn light on"""
    
    def __init__(self, light: Light):
        self._light = light
    
    def execute(self) -> None:
        self._light.turn_on()
    
    def undo(self) -> None:
        self._light.turn_off()