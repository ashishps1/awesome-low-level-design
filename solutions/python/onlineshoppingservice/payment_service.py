from payment_strategy import PaymentStrategy

class PaymentService:
    def process_payment(self, strategy: PaymentStrategy, amount: float) -> bool:
        return strategy.pay(amount)