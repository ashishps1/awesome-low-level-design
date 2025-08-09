from splitwise_service import SplitwiseService
from expense import Expense
from split_strategy import EqualSplitStrategy, ExactSplitStrategy, PercentageSplitStrategy

class SplitwiseDemo:
    @staticmethod
    def main():
        # 1. Setup the service
        service = SplitwiseService.get_instance()
        
        # 2. Create users and groups
        alice = service.add_user("Alice", "alice@a.com")
        bob = service.add_user("Bob", "bob@b.com")
        charlie = service.add_user("Charlie", "charlie@c.com")
        david = service.add_user("David", "david@d.com")
        
        friends_group = service.add_group("Friends Trip", [alice, bob, charlie, david])
        
        print("--- System Setup Complete ---\n")
        
        # 3. Use Case 1: Equal Split
        print("--- Use Case 1: Equal Split ---")
        service.create_expense(Expense.ExpenseBuilder()
                              .set_description("Dinner")
                              .set_amount(1000)
                              .set_paid_by(alice)
                              .set_participants([alice, bob, charlie, david])
                              .set_split_strategy(EqualSplitStrategy()))
        
        service.show_balance_sheet(alice.get_id())
        service.show_balance_sheet(bob.get_id())
        print()
        
        # 4. Use Case 2: Exact Split
        print("--- Use Case 2: Exact Split ---")
        service.create_expense(Expense.ExpenseBuilder()
                              .set_description("Movie Tickets")
                              .set_amount(370)
                              .set_paid_by(alice)
                              .set_participants([bob, charlie])
                              .set_split_strategy(ExactSplitStrategy())
                              .set_split_values([120.0, 250.0]))
        
        service.show_balance_sheet(alice.get_id())
        service.show_balance_sheet(bob.get_id())
        print()
        
        # 5. Use Case 3: Percentage Split
        print("--- Use Case 3: Percentage Split ---")
        service.create_expense(Expense.ExpenseBuilder()
                              .set_description("Groceries")
                              .set_amount(500)
                              .set_paid_by(david)
                              .set_participants([alice, bob, charlie])
                              .set_split_strategy(PercentageSplitStrategy())
                              .set_split_values([40.0, 30.0, 30.0]))  # 40%, 30%, 30%
        
        print("--- Balances After All Expenses ---")
        service.show_balance_sheet(alice.get_id())
        service.show_balance_sheet(bob.get_id())
        service.show_balance_sheet(charlie.get_id())
        service.show_balance_sheet(david.get_id())
        print()
        
        # 6. Use Case 4: Simplify Group Debts
        print("--- Use Case 4: Simplify Group Debts for 'Friends Trip' ---")
        simplified_debts = service.simplify_group_debts(friends_group.get_id())
        if not simplified_debts:
            print("All debts are settled within the group!")
        else:
            for debt in simplified_debts:
                print(debt)
        print()
        
        service.show_balance_sheet(bob.get_id())
        
        # 7. Use Case 5: Partial Settlement
        print("--- Use Case 5: Partial Settlement ---")
        # From the simplified debts, we see Bob should pay Alice. Let's say Bob pays 100.
        service.settle_up(bob.get_id(), alice.get_id(), 100)
        
        print("--- Balances After Partial Settlement ---")
        service.show_balance_sheet(alice.get_id())
        service.show_balance_sheet(bob.get_id())

if __name__ == "__main__":
    SplitwiseDemo.main()