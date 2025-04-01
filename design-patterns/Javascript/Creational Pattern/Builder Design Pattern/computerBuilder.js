class Computer {
  constructor(builder) {
    this.cpu = builder.cpu;
    this.ram = builder.ram;
    this.hardDisk = builder.hardDisk;
    this.moniter = builder.moniter;
  }
}

class ComputerBuilder {
  constructor(cpu, ram) {
    this.cpu = cpu;
    this.ram = ram;
  }

  // Methods with chaining
  addStorage(hardDisk) {
    this.hardDisk = hardDisk;
    return this;
  }

  addMoniter(moniter) {
    this.moniter = moniter;
    return this;
  }

  build() {
    return new Computer(this); // Pass the builder methods to the computer
  }
}

module.exports = ComputerBuilder;