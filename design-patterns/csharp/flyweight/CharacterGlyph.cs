using System;

namespace Flyweight
{
    public class CharacterGlyph : ICharacterFlyweight
    {
        private readonly char symbol;
        private readonly string fontFamily;
        private readonly int fontSize;
        private readonly string color;

        public CharacterGlyph(char symbol, string fontFamily, int fontSize, string color)
        {
            this.symbol = symbol;
            this.fontFamily = fontFamily;
            this.fontSize = fontSize;
            this.color = color;
        }

        public void Draw(int x, int y)
        {
            Console.WriteLine($"Rendering {symbol} at ({x}, {y}) with font {fontFamily}, size {fontSize}, color {color}");
        }
    }
} 