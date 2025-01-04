const TextEditor = require("./orginator");
const Caretaker = require("./careTaker");

// Create a TextEditor instance
const textEditor = new TextEditor();
const caretaker = new Caretaker();

// Write some content
textEditor.write("Hello, ");
caretaker.saveMemento(textEditor.save()); // Save the current state

textEditor.write("world!");
console.log(textEditor.getContent()); // Output: "Hello, world!"

caretaker.saveMemento(textEditor.save()); // Save the current state again

textEditor.write(" How are you?");
console.log(textEditor.getContent()); // Output: "Hello, world! How are you?"

// Restore to the previous state
textEditor.restore(caretaker.getMemento(1));
console.log(textEditor.getContent()); // Output: "Hello, world!"

// Restore to the initial state
textEditor.restore(caretaker.getMemento(0));
console.log(textEditor.getContent()); // Output: "Hello, "
