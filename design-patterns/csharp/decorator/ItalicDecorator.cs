using System;

namespace Decorator
{
    public class ItalicDecorator : TextDecorator
    {
        public ItalicDecorator(ITextView inner) : base(inner)
        {
        }

        public override void Render()
        {
            Console.Write("<i>");
            inner.Render();
            Console.Write("</i>");
        }
    }
} 