class PaymentProcessor {
  public process(price: number, paid: number): number {
    console.log("Processing Payment...");
    return paid - price;
  }
}
export default PaymentProcessor;