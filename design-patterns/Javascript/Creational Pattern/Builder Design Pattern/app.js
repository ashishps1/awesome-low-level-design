const ComputerBuilder = require("./computerBuilder");

const myComputer = new ComputerBuilder("Intel", "4GB")
  .addStorage("1TB")
  .addMoniter("LG")
  .build(); // Finally build the computer

console.log(myComputer);