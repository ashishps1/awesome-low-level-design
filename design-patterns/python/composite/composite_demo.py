from .developer import Developer
from .designer import Designer
from .manager import Manager


def composite_demo():
    """Demonstrate Composite pattern with organization hierarchy"""
    print("=== Composite Pattern Demo ===")
    
    # Create leaf employees
    dev1 = Developer("John", "Senior Developer", 85000)
    dev2 = Developer("Alice", "Junior Developer", 65000)
    dev3 = Developer("Bob", "Lead Developer", 95000)
    
    designer1 = Designer("Sarah", "UI Designer", 70000)
    designer2 = Designer("Mike", "UX Designer", 75000)
    
    # Create composite managers
    dev_manager = Manager("David", "Development Manager", 120000)
    design_manager = Manager("Emma", "Design Manager", 110000)
    
    # Build hierarchy
    dev_manager.add_employee(dev1)
    dev_manager.add_employee(dev2)
    dev_manager.add_employee(dev3)
    
    design_manager.add_employee(designer1)
    design_manager.add_employee(designer2)
    
    # Create top-level manager
    cto = Manager("Lisa", "CTO", 200000)
    cto.add_employee(dev_manager)
    cto.add_employee(design_manager)
    
    # Demonstrate composite behavior
    print("=== Organization Structure ===")
    cto.show_details()
    
    print(f"\n=== Total Organization Salary Cost ===")
    print(f"Total salary cost: ${cto.get_salary():,.2f}")
    
    print(f"\n=== Department Costs ===")
    print(f"Development team cost: ${dev_manager.get_salary():,.2f}")
    print(f"Design team cost: ${design_manager.get_salary():,.2f}")
    
    print(f"\n=== Individual Employee Details ===")
    dev1.show_details()
    designer1.show_details()


if __name__ == "__main__":
    composite_demo()