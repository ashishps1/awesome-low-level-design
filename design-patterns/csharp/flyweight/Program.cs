using System;

namespace Flyweight
{
    class Program
    {
        static void Main(string[] args)
        {
            var editor = new TextEditorClient();

            // Render 'Hello' with the same style
            string word = "Hello";
            for (int i = 0; i < word.Length; i++)
            {
                editor.AddCharacter(word[i], 10 + i * 15, 50, "Arial", 14, "#000000");
            }

            // Render 'World' with a different font and color
            string word2 = "World";
            for (int i = 0; i < word2.Length; i++)
            {
                editor.AddCharacter(word2[i], 10 + i * 15, 100, "Times New Roman", 14, "#3333FF");
            }

            editor.RenderDocument();
        }
    }
} 