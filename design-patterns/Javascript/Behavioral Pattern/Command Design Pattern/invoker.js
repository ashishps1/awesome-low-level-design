// Invoker class
class RemoteControl {
    setCommand(command) {
      this.command = command;
    }
  
    pressButton() {
      this.command.execute();
    }
  }

  module.exports = {RemoteControl}
  