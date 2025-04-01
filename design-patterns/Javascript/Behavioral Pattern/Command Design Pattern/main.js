// Client code

const {
  LightOnCommand,
  LightOffCommand,
  FanOnCommand,
  FanOffCommand,
} = require("./command");

const{Light, Fan} = require('./receiver')

const {RemoteControl} = require ('./invoker')

const light = new Light();
const fan = new Fan();

const lightOn = new LightOnCommand(light);
const lightOff = new LightOffCommand(light);

const fanOn = new FanOnCommand(fan);
const fanOff = new FanOffCommand(fan);

const remote = new RemoteControl();

// Turning on the light
remote.setCommand(lightOn);
remote.pressButton(); // Output: "The light is on."

// Turning off the light
remote.setCommand(lightOff);
remote.pressButton(); // Output: "The light is off."

// Turning on the fan
remote.setCommand(fanOn);
remote.pressButton(); // Output: "The fan is on."

// Turning off the fan
remote.setCommand(fanOff);
remote.pressButton(); // Output: "The fan is off."
