import { Coin } from "../Coin";

export default interface VendingMachineState {
  insertCoin(coin: Coin): void;
  selectItem(code: string): void;
  dispense(): void;
  refund(): void;
}
