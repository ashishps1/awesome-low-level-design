from .character_flyweight import CharacterFlyweight

class CharacterGlyph(CharacterFlyweight):
    def __init__(self, symbol: str, font_family: str, font_size: int, color: str):
        self.symbol = symbol
        self.font_family = font_family
        self.font_size = font_size
        self.color = color

    def draw(self, x: int, y: int) -> None:
        print(f"Rendering {self.symbol} at ({x}, {y}) with font {self.font_family}, "
              f"size {self.font_size}, color {self.color}") 