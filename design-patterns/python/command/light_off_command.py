from .command import Command
from .light import Light


class LightOffCommand(Command):
    """Concrete Command - Turn light off"""
    
    def __init__(self, light: Light):
        self._light = light
    
    def execute(self) -> None:
        self._light.turn_off()
    
    def undo(self) -> None:
        self._light.turn_on()