using System;
using System.Collections.Generic;

namespace Memento
{
    public class TextEditorUndoManager
    {
        private readonly Stack<TextEditorMemento> history = new Stack<TextEditorMemento>();

        public void Save(TextEditor editor)
        {
            history.Push(editor.Save());
        }

        public void Undo(TextEditor editor)
        {
            if (history.Count > 0)
            {
                editor.Restore(history.Pop());
            }
            else
            {
                Console.WriteLine("Nothing to undo.");
            }
        }
    }
} 