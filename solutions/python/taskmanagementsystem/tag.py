class Tag:
    def __init__(self, name: str):
        self._name = name
    
    @property
    def name(self) -> str:
        return self._name