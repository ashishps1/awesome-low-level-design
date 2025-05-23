using System;

namespace Mediator
{
    public class Label : UIComponent
    {
        private string text;

        public Label(IUIMediator mediator) : base(mediator)
        {
        }

        public void SetText(string message)
        {
            this.text = message;
            Console.WriteLine($"Status: {text}");
        }
    }
} 