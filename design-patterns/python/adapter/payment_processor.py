from abc import ABC, abstractmethod


class PaymentProcessor(ABC):
    """Target Interface"""
    @abstractmethod
    def process_payment(self, amount: float, currency: str) -> None:
        pass

    @abstractmethod
    def is_payment_successful(self) -> bool:
        pass

    @abstractmethod
    def get_transaction_id(self) -> str:
        pass 