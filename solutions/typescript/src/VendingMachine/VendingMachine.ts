import { Coin } from "./Coin";
import Inventory from "./Inventory";
import Item from "./Item";
import DispensingState from "./VendingMachineState/DispensingState";
import HasMoneyState from "./VendingMachineState/HasMoneyState";
import IdleState from "./VendingMachineState/IdleState";
import ItemSelectedState from "./VendingMachineState/ItemSelectedState";
import VendingMachineState from "./VendingMachineState/VendingMachineState";

export default class VendingMachine {
  private static instance: VendingMachine | null;

  private inventory: Inventory;
  private selectedItemCode: string | null;
  private balance: number;

  private currentState: VendingMachineState;
  private idleState: VendingMachineState;
  private itemSelectedState: VendingMachineState;
  private hasMoneyState: VendingMachineState;
  private dispensingState: VendingMachineState;

  private constructor() {
    this.inventory = new Inventory();
    this.idleState = new IdleState(this);
    this.itemSelectedState = new ItemSelectedState(this);
    this.hasMoneyState = new HasMoneyState(this);
    this.dispensingState = new DispensingState(this);
    this.currentState = this.idleState;
    this.balance = 0;
    this.selectedItemCode = null;
  }

  static getInstance() {
    if (VendingMachine.instance == null) {
      VendingMachine.instance = new VendingMachine();
    }
    return VendingMachine.instance;
  }

  insertCoin(coin: Coin) {
    this.currentState.insertCoin(coin);
  }

  addItem(code: string, name: string, price: number, quantity: number) {
    const item = new Item(code, name, price);
    this.inventory.addItem(code, item, quantity);
    return item;
  }

  selectItem(code: string) {
    this.currentState.selectItem(code);
  }

  dispense() {
    this.currentState.dispense();
  }

  dispenseItem() {
    if (!this.selectedItemCode) {
      throw new Error("No Item Selected Yet");
    }

    const item = this.inventory.getItem(this.selectedItemCode);
    if (!item) {
      throw new Error("Item Not In Inventory");
    }

    if (this.balance >= item.getPrice()) {
      this.inventory.reduceStock(this.selectedItemCode);
      this.balance -= item.getPrice();
      console.log("Dispensed: " + item.getName());
      if (this.balance > 0) {
        console.log("Returning change: " + this.balance);
      }
    }
    this.resetToIdleState();
    this.setState(this.getIdleState());
  }

  refundBalance() {
    console.log("Refunding: " + this.balance);
    this.balance = 0;
  }

  resetToIdleState() {
    this.selectedItemCode = null;
    this.balance = 0;
  }

  addBalance(value: number) {
    this.balance += value;
  }

  //Getter, Setters
  getIdleState() {
    return this.idleState;
  }

  getItemSelectedState() {
    return this.itemSelectedState;
  }

  getHasMoneyState() {
    return this.hasMoneyState;
  }

  getDispensingState() {
    return this.dispensingState;
  }

  getInventory() {
    return this.inventory;
  }

  getSelectedItem() {
    if (!this.selectedItemCode) {
      throw new Error("No Item Selected Yet");
    }
    return this.inventory.getItem(this.selectedItemCode);
  }

  setSelectedItemCode(code: string) {
    this.selectedItemCode = code;
  }

  getBalance() {
    return this.balance;
  }

  setState(state: VendingMachineState) {
    this.currentState = state;
  }
}
