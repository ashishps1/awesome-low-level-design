using System;

namespace Decorator
{
    public class UnderlineDecorator : TextDecorator
    {
        public UnderlineDecorator(ITextView inner) : base(inner)
        {
        }

        public override void Render()
        {
            Console.Write("<u>");
            inner.Render();
            Console.Write("</u>");
        }
    }
} 