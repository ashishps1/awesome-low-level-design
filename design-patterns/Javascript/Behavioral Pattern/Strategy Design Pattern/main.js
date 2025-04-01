const ShoppinCart = require("./shoppingCart_Context");
const { Cash, UPI, Card, InternetBanking } = require("./paymentStrategy");

// Creating a shopping cart Instance
const shoppingCart = new ShoppinCart();

// Adding items to the shopping cart
shoppingCart.addItem({ name: "Laptop", price: 500 });
shoppingCart.addItem({ name: "Mobile", price: 200 });
shoppingCart.addItem({ name: "TV", price: 1000 });

// View cart after adding items
shoppingCart.viewCart();

// Checkout in method - 1
shoppingCart.setPaymentMethod(new Card(123456789, 123));
shoppingCart.checkout();

// Checkout in method - 2
shoppingCart.setPaymentMethod(new Cash(123));
shoppingCart.checkout();

// Checkout in method - 3
shoppingCart.setPaymentMethod(new UPI(123456789, 123));
shoppingCart.checkout();
