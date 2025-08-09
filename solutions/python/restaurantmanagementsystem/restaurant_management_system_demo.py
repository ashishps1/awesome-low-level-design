from restaurant_management_system_facade import RestaurantManagementSystemFacade

class RestaurantManagementSystemDemo:
    @staticmethod
    def main():
        # --- 1. System Setup using the Restaurant Singleton ---
        print("=== Initializing Restaurant System ===")
        rms_facade = RestaurantManagementSystemFacade.get_instance()
        
        # --- 2. Add table and staff ---
        table1 = rms_facade.add_table(1, 4)
        chef1 = rms_facade.add_chef("CHEF01", "Gordon")
        waiter1 = rms_facade.add_waiter("W01", "Alice")
        
        # --- 3. Add menu items ---
        pizza = rms_facade.add_menu_item("PIZZA01", "Margherita Pizza", 12.50)
        pasta = rms_facade.add_menu_item("PASTA01", "Carbonara Pasta", 15.00)
        coke = rms_facade.add_menu_item("DRINK01", "Coke", 2.50)
        print("Initialization Complete.\n")
        
        # --- 4. Scenario: A waiter takes an order for a table ---
        # The Command Pattern is used inside the rms_facade.take_order() method.
        print("=== SCENARIO 1: Taking an order ===")
        order1 = rms_facade.take_order(table1.id, waiter1.id, [pizza.get_id(), coke.get_id()])
        print(f"Order taken successfully. Order ID: {order1.order_id}")
        
        # --- 5. Scenario: Chef prepares food and notifies waiter ---
        print("\n=== SCENARIO 2: Chef prepares, Waiter gets notified ===")
        rms_facade.mark_items_as_ready(order1.order_id)
        rms_facade.serve_order(waiter1.id, order1.order_id)
        
        # --- 6. Scenario: Generate a bill with taxes and service charges ---
        # The Decorator Pattern is used inside rms_facade.generate_bill().
        print("\n=== SCENARIO 3: Generating the bill ===")
        final_bill = rms_facade.generate_bill(order1.order_id)
        final_bill.print_bill()

if __name__ == "__main__":
    RestaurantManagementSystemDemo.main()