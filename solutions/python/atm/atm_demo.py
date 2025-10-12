from atm import ATM
from operation_type import OperationType

class ATMDemo:
    @staticmethod
    def main():
        atm = ATM.get_instance()
        
        # Perform Check Balance operation
        atm.insert_card("1234-5678-9012-3456")
        atm.enter_pin("1234")
        atm.select_operation(OperationType.CHECK_BALANCE)  # $1000
        
        # Perform Withdraw Cash operation
        atm.insert_card("1234-5678-9012-3456")
        atm.enter_pin("1234")
        atm.select_operation(OperationType.WITHDRAW_CASH, 570)
        
        # Perform Deposit Cash operation
        atm.insert_card("1234-5678-9012-3456")
        atm.enter_pin("1234")
        atm.select_operation(OperationType.DEPOSIT_CASH, 200)
        
        # Perform Check Balance operation
        atm.insert_card("1234-5678-9012-3456")
        atm.enter_pin("1234")
        atm.select_operation(OperationType.CHECK_BALANCE)  # $630
        
        # Perform Withdraw Cash more than balance
        atm.insert_card("1234-5678-9012-3456")
        atm.enter_pin("1234")
        atm.select_operation(OperationType.WITHDRAW_CASH, 700)  # Insufficient balance
        
        # Insert Incorrect PIN
        atm.insert_card("1234-5678-9012-3456")
        atm.enter_pin("3425")

if __name__ == "__main__":
    ATMDemo.main()