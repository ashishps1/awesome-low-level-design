from user import User
from group import Group
from expense import Expense
from equal_split import EqualSplit
from percent_split import PercentSplit
from splitwise_service import SplitwiseService

class SplitwiseDemo:
    @staticmethod
    def run():
        splitwise_service = SplitwiseService.get_instance()

        # Create users
        user1 = User("1", "Alice", "alice@example.com")
        user2 = User("2", "Bob", "bob@example.com")
        user3 = User("3", "Charlie", "charlie@example.com")

        splitwise_service.add_user(user1)
        splitwise_service.add_user(user2)
        splitwise_service.add_user(user3)

        # Create a group
        group = Group("1", "Apartment")
        group.add_member(user1)
        group.add_member(user2)
        group.add_member(user3)

        splitwise_service.add_group(group)

        # Add an expense
        expense = Expense("1", 300.0, "Rent", user1)
        equal_split1 = EqualSplit(user1)
        equal_split2 = EqualSplit(user2)
        percent_split = PercentSplit(user3, 20.0)

        expense.add_split(equal_split1)
        expense.add_split(equal_split2)
        expense.add_split(percent_split)

        splitwise_service.add_expense(group.get_id(), expense)

        # Settle balances
        splitwise_service.settle_balance(user1.get_id(), user2.get_id())
        splitwise_service.settle_balance(user1.get_id(), user3.get_id())

        # Print user balances
        for user in [user1, user2, user3]:
            print(f"User: {user.get_name()}")
            for key, value in user.get_balances().items():
                print(f"  Balance with {key}: {value}")


if __name__ == "__main__":
    SplitwiseDemo.run()