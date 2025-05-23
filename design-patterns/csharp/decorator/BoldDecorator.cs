using System;

namespace Decorator
{
    public class BoldDecorator : TextDecorator
    {
        public BoldDecorator(ITextView inner) : base(inner)
        {
        }

        public override void Render()
        {
            Console.Write("<b>");
            inner.Render();
            Console.Write("</b>");
        }
    }
} 