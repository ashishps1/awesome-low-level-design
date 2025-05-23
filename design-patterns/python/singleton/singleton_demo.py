from .eager_singleton import EagerSingleton
from .lazy_singleton import LazySingleton
from .thread_safe_singleton import ThreadSafeSingleton
from .double_checked_singleton import DoubleCheckedSingleton
from .bill_pugh_singleton import BillPughSingleton
from .enum_singleton import EnumSingleton


def singleton_demo():
    """Demonstrate various singleton implementations"""
    print("=== Singleton Pattern Demo ===")
    
    # Eager Singleton
    print("\n--- Eager Singleton ---")
    eager1 = EagerSingleton()
    eager2 = EagerSingleton()
    print(f"Same instance: {eager1 is eager2}")
    print(f"Message: {eager1.get_message()}")
    
    # Lazy Singleton
    print("\n--- Lazy Singleton ---")
    lazy1 = LazySingleton()
    lazy2 = LazySingleton()
    print(f"Same instance: {lazy1 is lazy2}")
    print(f"Message: {lazy1.get_message()}")
    
    # Thread Safe Singleton
    print("\n--- Thread Safe Singleton ---")
    thread_safe1 = ThreadSafeSingleton()
    thread_safe2 = ThreadSafeSingleton()
    print(f"Same instance: {thread_safe1 is thread_safe2}")
    print(f"Message: {thread_safe1.get_message()}")
    
    # Double Checked Singleton
    print("\n--- Double Checked Singleton ---")
    double_checked1 = DoubleCheckedSingleton()
    double_checked2 = DoubleCheckedSingleton()
    print(f"Same instance: {double_checked1 is double_checked2}")
    print(f"Message: {double_checked1.get_message()}")
    
    # Bill Pugh Singleton
    print("\n--- Bill Pugh Singleton ---")
    bill_pugh1 = BillPughSingleton.get_instance()
    bill_pugh2 = BillPughSingleton.get_instance()
    print(f"Same instance: {bill_pugh1 is bill_pugh2}")
    print(f"Message: {bill_pugh1.get_message()}")
    
    # Enum Singleton
    print("\n--- Enum Singleton ---")
    enum1 = EnumSingleton.get_instance()
    enum2 = EnumSingleton.get_instance()
    print(f"Same instance: {enum1 is enum2}")
    print(f"Message: {enum1.get_message()}")


if __name__ == "__main__":
    singleton_demo()