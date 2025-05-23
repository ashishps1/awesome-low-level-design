import time


class LegacyGateway:
    """Adaptee - The old interface that needs to be adapted"""
    
    def __init__(self):
        self._transaction_reference = None
        self._is_payment_successful = False
    
    def execute_transaction(self, total_amount: float, currency: str) -> None:
        print(f"LegacyGateway: Executing transaction for {currency} {total_amount}")
        self._transaction_reference = int(time.time() * 1000000)  # Using microseconds for uniqueness
        self._is_payment_successful = True
        print(f"LegacyGateway: Transaction executed successfully. Txn ID: {self._transaction_reference}")
    
    def check_status(self, transaction_reference: int) -> bool:
        print(f"LegacyGateway: Checking status for ref: {transaction_reference}")
        return self._is_payment_successful
    
    def get_reference_number(self) -> int:
        return self._transaction_reference 