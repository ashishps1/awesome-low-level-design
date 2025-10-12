from enum import Enum

class OperationType(Enum):
    CHECK_BALANCE = "CHECK_BALANCE"
    WITHDRAW_CASH = "WITHDRAW_CASH"
    DEPOSIT_CASH = "DEPOSIT_CASH"