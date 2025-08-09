class InsufficientFundsException(Exception):
    def __init__(self, message: str):
        super().__init__(message)

class InsufficientStockException(Exception):
    def __init__(self, message: str):
        super().__init__(message)