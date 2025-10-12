class Player:
    def __init__(self, name: str):
        self.name = name
        self.position = 0

    def get_name(self) -> str:
        return self.name

    def get_position(self) -> int:
        return self.position

    def set_position(self, position: int):
        self.position = position