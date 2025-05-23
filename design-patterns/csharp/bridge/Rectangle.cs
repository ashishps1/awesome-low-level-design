namespace Bridge
{
    public class Rectangle : Shape
    {
        private readonly float width;
        private readonly float height;

        public Rectangle(IRenderer renderer, float width, float height) : base(renderer)
        {
            this.width = width;
            this.height = height;
        }

        public override void Draw()
        {
            renderer.RenderRectangle(width, height);
        }
    }
} 