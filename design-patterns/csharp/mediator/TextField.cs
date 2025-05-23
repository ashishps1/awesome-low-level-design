using System;

namespace Mediator
{
    public class TextField : UIComponent
    {
        private string text = "";

        public TextField(IUIMediator mediator) : base(mediator)
        {
        }

        public void SetText(string newText)
        {
            this.text = newText;
            Console.WriteLine($"TextField updated: {newText}");
            NotifyMediator();
        }

        public string GetText()
        {
            return text;
        }
    }
} 