using System;
using System.Collections.Generic;

namespace Flyweight
{
    public class TextEditorClient
    {
        private readonly CharacterFlyweightFactory factory = new();
        private readonly List<RenderedCharacter> document = new();

        public void AddCharacter(char c, int x, int y, string font, int size, string color)
        {
            ICharacterFlyweight glyph = CharacterFlyweightFactory.GetFlyweight(c, font, size, color);
            document.Add(new RenderedCharacter(glyph, x, y));
        }

        public void RenderDocument()
        {
            foreach (var rc in document)
            {
                rc.Draw();
            }
            Console.WriteLine($"Total flyweight objects used: {factory.GetFlyweightCount()}");
        }

        private class RenderedCharacter
        {
            private readonly ICharacterFlyweight glyph;
            private readonly int x, y;

            public RenderedCharacter(ICharacterFlyweight glyph, int x, int y)
            {
                this.glyph = glyph;
                this.x = x;
                this.y = y;
            }

            public void Draw()
            {
                glyph.Draw(x, y);
            }
        }
    }
} 