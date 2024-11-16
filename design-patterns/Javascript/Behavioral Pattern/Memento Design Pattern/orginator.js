// Orginator file

const Memento = require("./memento");

class TextEditor {
  constructor() {
    this.content = "";
  }

  write(content) {
    this.content += content;
  }

  getContent() {
    return this.content;
  }

  save() {
    return new Memento(this.content);
  }

  restore(memento) {
    this.content = memento.getState();
  }
}

module.exports = TextEditor;
