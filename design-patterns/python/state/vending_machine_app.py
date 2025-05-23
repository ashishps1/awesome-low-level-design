from .vending_machine import VendingMachine


def vending_machine_app():
    """Demonstrate State pattern with vending machine"""
    print("=== State Pattern Demo - Vending Machine ===")
    
    machine = VendingMachine()
    print(f"Initial state: {machine.current_state}")
    
    # Scenario 1: Normal purchase
    print("\n--- Scenario 1: Normal Purchase ---")
    machine.select_item()  # Should ask for coin first
    machine.insert_coin(1.00)
    machine.select_item()  # Should ask for more money
    machine.insert_coin(0.50)
    machine.select_item()  # Should dispense item
    
    print(f"Final state: {machine.current_state}")
    
    # Scenario 2: Cancel transaction
    print("\n--- Scenario 2: Cancel Transaction ---")
    machine.insert_coin(1.00)
    machine.cancel_transaction()  # Should return money and go to idle
    
    # Scenario 3: Exact change
    print("\n--- Scenario 3: Exact Change ---")
    machine.insert_coin(1.50)  # Exact amount
    machine.select_item()  # Should dispense immediately
    
    # Scenario 4: Over payment
    print("\n--- Scenario 4: Over Payment ---")
    machine.insert_coin(2.00)  # More than needed
    machine.select_item()  # Should dispense and return change
    
    # Scenario 5: Try operations during dispensing
    print("\n--- Scenario 5: Operations During Dispensing ---")
    machine.insert_coin(1.50)
    machine.select_item()
    # This will be in dispensing state briefly
    machine.insert_coin(1.00)  # Should be rejected
    machine.cancel_transaction()  # Should be rejected


if __name__ == "__main__":
    vending_machine_app()