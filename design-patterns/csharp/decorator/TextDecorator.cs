namespace Decorator
{
    public abstract class TextDecorator : ITextView
    {
        protected readonly ITextView inner;

        public TextDecorator(ITextView inner)
        {
            this.inner = inner;
        }

        public abstract void Render();
    }
} 