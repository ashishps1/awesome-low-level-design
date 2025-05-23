from .sole import Sole
from .shoe_lace import ShoeLace


class Shoe:
    """Product that uses components from Abstract Factory"""
    
    def __init__(self, sole: Sole, shoe_lace: ShoeLace):
        self._sole = sole
        self._shoe_lace = shoe_lace
    
    def describe(self) -> str:
        return f"Shoe with {self._sole.get_sole_type()} and {self._shoe_lace.get_lace_type()}"
    
    @property
    def sole(self) -> Sole:
        return self._sole
    
    @property
    def shoe_lace(self) -> ShoeLace:
        return self._shoe_lace