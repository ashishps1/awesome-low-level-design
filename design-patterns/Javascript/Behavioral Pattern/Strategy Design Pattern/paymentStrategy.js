// Strategy class

// Abstract class

class PaymentGateway {
  pay(amount) {
    throw new Error("Method 'pay()' must be implemented!");
  }
}

// Concrete class for paymentGateway

// Cash payment method
class Cash extends PaymentGateway {
  pay(amount) {
    console.log(`Payment of ${amount} done using Cash`);
  }
}

// UPI payment method
class UPI extends PaymentGateway {
  constructor(UPI_ID, UPI_PIN) {
    super();
    this.UPI_ID = UPI_ID;
    this.UPI_PIN = UPI_PIN;
  }
  pay(amount) {
    console.log(
      `Payment of ${amount} done using UPI with ID ${this.UPI_ID} and PIN ${this.UPI_PIN}`
    );
  }
}

// Card payment method
class Card extends PaymentGateway {
  constructor(cardNumber, CVV) {
    super();
    this.cardNumber = cardNumber;
    this.CVV = CVV;
  }
  pay(amount) {
    console.log(
      `Payment of ${amount} done using Card Number ${this.cardNumber} and CVV ${this.CVV}`
    );
  }
}

// Internet Banking payment method
class InternetBanking extends PaymentGateway {
  constructor(accountNumber, IFSC) {
    super();
    this.accountNumber = accountNumber;
    this.IFSC = IFSC;
  }
  pay(amount) {
    console.log(
      `Payment of ${amount} done using Internet Banking with Account Number ${this.accountNumber} and IFSC ${this.IFSC}`
    );
  }
}

module.exports = { Cash, UPI, Card, InternetBanking };
