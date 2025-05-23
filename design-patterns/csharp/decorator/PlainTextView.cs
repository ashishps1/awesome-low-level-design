using System;

namespace Decorator
{
    public class PlainTextView : ITextView
    {
        private readonly string text;

        public PlainTextView(string text)
        {
            this.text = text;
        }

        public void Render()
        {
            Console.Write(text);
        }
    }
} 