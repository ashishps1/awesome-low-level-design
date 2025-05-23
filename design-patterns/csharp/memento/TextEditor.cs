using System;

namespace Memento
{
    public class TextEditor
    {
        private string content = "";

        public void Type(string newText)
        {
            content += newText;
            Console.WriteLine($"Typed: {newText}");
        }

        public string GetContent()
        {
            return content;
        }

        public TextEditorMemento Save()
        {
            Console.WriteLine($"Saving state: \"{content}\"");
            return new TextEditorMemento(content);
        }

        public void Restore(TextEditorMemento memento)
        {
            content = memento.GetState();
            Console.WriteLine($"Restored state to: \"{content}\"");
        }
    }
} 