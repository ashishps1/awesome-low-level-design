namespace Memento
{
    public class TextEditorMemento
    {
        private readonly string state;

        public TextEditorMemento(string state)
        {
            this.state = state;
        }

        public string GetState()
        {
            return state;
        }
    }
} 