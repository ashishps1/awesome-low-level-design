from threading import Lock

class PaymentProcessor:
    _instance = None
    _lock = Lock()

    def __new__(cls):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def process_payment(self, payment):
        # Process payment using the selected payment method
        payment.process_payment()