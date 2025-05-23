using System;

namespace Decorator
{
    class Program
    {
        static void Main(string[] args)
        {
            ITextView plain = new PlainTextView("Hello, world!");

            Console.Write("Plain: ");
            plain.Render();
            Console.WriteLine();

            Console.Write("Bold: ");
            ITextView bold = new BoldDecorator(plain);
            bold.Render();
            Console.WriteLine();

            Console.Write("Italic + Bold: ");
            ITextView italicBold = new ItalicDecorator(bold);
            italicBold.Render();
            Console.WriteLine();

            Console.Write("Underline + Italic + Bold: ");
            ITextView fullStyle = new UnderlineDecorator(italicBold);
            fullStyle.Render();
            Console.WriteLine();
        }
    }
} 