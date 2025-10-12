import { Coin } from "../Coin";
import VendingMachine from "../VendingMachine";
import VendingMachineState from "./VendingMachineState";

export default class ItemSelectedState implements VendingMachineState {
    private machine: VendingMachine;

    constructor(machine: VendingMachine) {
        this.machine = machine;
    }

    insertCoin(coin: Coin) {
        const price = this.machine.getSelectedItem()?.getPrice();
        if (!price) {
            throw new Error("Item Not Selected Yet.");
        }

        this.machine.addBalance(coin);
        console.log("Coin Inserted: " + coin);

        if (this.machine.getBalance() >= price) {
            console.log("Sufficient money received.");
            this.machine.setState(this.machine.getHasMoneyState());
        }
    }

    selectItem() {
        console.log("Item already selected.");
    }

    dispense() {
        console.log("Please insert sufficient money.");
    }

    refund() {
        this.machine.resetToIdleState();
        this.machine.setState(this.machine.getIdleState());
    }
}
