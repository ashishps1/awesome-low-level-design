// Context file as shoppingCart class

class ShoppinCart {
  constructor() {
    this.items = [];
    this.paymentMethod = null;
  }

  // Adding items to the shopping cart
  addItem(item) {
    this.items.push(item);
  }

  // View cart after adding items
  viewCart() {
    console.log("Your cart contains: ");
    this.items.forEach((item, index) => {
      console.log(`${index + 1}. ${item.name} - $${item.price}`);
    });
  }

  // Selecting the payment method
  setPaymentMethod(paymentMethod) {
    this.paymentMethod = paymentMethod;
  }

  // Checkout
  checkout() {
    // Adding reduce method to calculate the total bill
    const Total = this.items.reduce((total, item) => total + item.price, 0);

    // Checks if paymentMethod is choosen to proceed for checkout
    if (this.paymentMethod) {
      console.log(`Total Bill: $${Total}`);
      this.paymentMethod.pay(Total);
    } else {
      console.log("Please confirm your payment method");
    }
  }
}
module.exports = ShoppinCart;
