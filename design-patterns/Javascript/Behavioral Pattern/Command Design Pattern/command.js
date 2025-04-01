// Abstract Command
class Command {
  execute() {}
}

// Concrete Command
class LightOnCommand extends Command {
  constructor(light) {
    super();
    this.light = light;
  }

  execute() {
    this.light.turnOn();
  }
}
class LightOffCommand extends Command {
  constructor(light) {
    super();
    this.light = light;
  }

  execute() {
    this.light.turnOff();
  }
}

// Concrete Command to turn on the fan
class FanOnCommand extends Command {
  constructor(fan) {
    super();
    this.fan = fan;
  }

  execute() {
    this.fan.turnOn();
  }
}

// Concrete Command to turn off the fan
class FanOffCommand extends Command {
  constructor(fan) {
    super();
    this.fan = fan;
  }

  execute() {
    this.fan.turnOff();
  }
}

module.exports = {
  LightOnCommand,
  LightOffCommand,
  FanOnCommand,
  FanOffCommand,
};
