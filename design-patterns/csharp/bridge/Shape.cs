namespace Bridge
{
    public abstract class Shape
    {
        protected readonly IRenderer renderer;

        protected Shape(IRenderer renderer)
        {
            this.renderer = renderer;
        }

        public abstract void Draw();
    }
} 