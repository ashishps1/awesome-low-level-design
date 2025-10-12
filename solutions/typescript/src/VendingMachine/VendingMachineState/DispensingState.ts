import VendingMachine from "../VendingMachine";
import VendingMachineState from "./VendingMachineState";

export default class DispensingState implements VendingMachineState {
  private machine: VendingMachine;

  constructor(machine: VendingMachine) {
    this.machine = machine;
  }

  insertCoin(): void {
    console.log("Currently dispensing. Please wait.");
  }

  selectItem() {
    console.log("Currently dispensing. Please wait.");
  }

  dispense() {
    // already triggered by HasMoneyState
  }

  refund() {
    console.log("Dispensing in progress. Refund not allowed.");
  }
}
