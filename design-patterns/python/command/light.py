class Light:
    """Receiver - The object that knows how to perform the operations"""
    
    def __init__(self, location: str):
        self._location = location
        self._is_on = False
    
    def turn_on(self) -> None:
        self._is_on = True
        print(f"{self._location} light is ON")
    
    def turn_off(self) -> None:
        self._is_on = False
        print(f"{self._location} light is OFF")
    
    @property
    def is_on(self) -> bool:
        return self._is_on
    
    @property
    def location(self) -> str:
        return self._location