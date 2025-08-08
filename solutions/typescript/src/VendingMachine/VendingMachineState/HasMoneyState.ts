import VendingMachine from "../VendingMachine";
import VendingMachineState from "./VendingMachineState";

export default class HasMoneyState implements VendingMachineState {
  private machine: VendingMachine;

  constructor(machine: VendingMachine) {
    this.machine = machine;
  }

  insertCoin() {
    console.log("Already received full amount.");
  }

  selectItem() {
    console.log("Item already selected.");
  }

  dispense() {
    this.machine.setState(this.machine.getDispensingState());
    this.machine.dispenseItem();
  }

  refund() {
    this.machine.refundBalance();
    this.machine.resetToIdleState();
    this.machine.setState(this.machine.getIdleState());
  }
}
