import VendingMachine from "../VendingMachine";
import VendingMachineState from "./VendingMachineState";

export default class IdleState implements VendingMachineState {
  private machine: VendingMachine;

  constructor(machine: VendingMachine) {
    this.machine = machine;
  }

  selectItem(code: string): void {
    if (!this.machine.getInventory().isAvailable(code)) {
      console.log("Item not available.");
      return;
    }

    this.machine.setSelectedItemCode(code);
    this.machine.setState(this.machine.getItemSelectedState());
    console.log("Item Selected = ", code);
  }

  insertCoin(): void {
    console.log("Please select the product first");
  }

  dispense(): void {
    console.log("Please select the product first");
  }

  refund(): void {
    console.log("Please select the product first");
  }
}
