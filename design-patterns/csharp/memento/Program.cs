using System;

namespace Memento
{
    class Program
    {
        static void Main(string[] args)
        {
            var editor = new TextEditor();
            var undoManager = new TextEditorUndoManager();

            // Type some text and save state
            editor.Type("Hello");
            undoManager.Save(editor);

            editor.Type(" World");
            undoManager.Save(editor);

            editor.Type("!");
            Console.WriteLine($"Current content: {editor.GetContent()}");

            // Undo twice
            Console.WriteLine("\nUndoing last change:");
            undoManager.Undo(editor);
            Console.WriteLine($"Content after undo: {editor.GetContent()}");

            Console.WriteLine("\nUndoing another change:");
            undoManager.Undo(editor);
            Console.WriteLine($"Content after second undo: {editor.GetContent()}");

            // Try to undo when nothing is left
            Console.WriteLine("\nTrying to undo when nothing is left:");
            undoManager.Undo(editor);
        }
    }
} 