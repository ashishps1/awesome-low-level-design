# Encapsulation in Python

## Introduction

**Encapsulation** is one of the four fundamental principles of Object-Oriented Programming (OOP). It is the practice of **bundling data (variables) and methods** that operate on that data into a single unit (class) while restricting direct access to the internal details.

Encapsulation in Python is achieved using:
1. **Access Modifiers** (`public`, `_protected`, `__private`)
2. **Getters and Setters**
3. **Data Hiding**

Encapsulation helps in **data protection, modularity, and maintainability** of the code.

## **What is Encapsulation?**

Encapsulation means **wrapping** the data (variables) and code (methods) together into a single unit (class). It restricts direct access to some of an object's components, which helps protect data integrity and prevents unintended modifications.

### **Key Benefits of Encapsulation**
- **Data Hiding**: Prevents direct access to sensitive data.
- **Increased Security**: Controls how data is accessed and modified.
- **Improved Code Maintainability**: Allows changes without affecting other parts of the code.
- **Better Modularity**: Organizes the code into logical components.

---

## **Encapsulation Using Access Modifiers**

Python provides **access modifiers** to enforce encapsulation:
- **`public`**: Accessible from anywhere.
- **`_protected`**: Accessible within the class and subclasses.
- **`__private`**: Accessible only within the class.

### **Example: Encapsulation with Private Variables**

```python
class BankAccount:
    def __init__(self, account_holder, balance):
        self.__account_holder = account_holder  # Private attribute
        self.__balance = balance  # Private attribute

    # Getter method to access balance
    def get_balance(self):
        return self.__balance

    # Setter method to modify balance
    def deposit(self, amount):
        if amount > 0:
            self.__balance += amount
            print(f"Deposited: {amount}")
        else:
            print("Invalid deposit amount")

# Usage
account = BankAccount("Alice", 1000)
print("Current Balance:", account.get_balance())
account.deposit(500)
print("Updated Balance:", account.get_balance())
```

### **Output:**
```
Current Balance: 1000
Deposited: 500
Updated Balance: 1500
```

**Why Use Encapsulation?**
- Prevents unauthorized access to the data.
- Allows controlled modifications through methods.

---

## **Encapsulation Using Getters and Setters**

Encapsulation ensures that **data cannot be directly accessed** but must be retrieved or modified through methods.

### **Example: Getters and Setters in Python**

```python
class Employee:
    def __init__(self):
        self.__name = ""
        self.__age = 0

    # Getter method
    def get_name(self):
        return self.__name

    # Setter method
    def set_name(self, name):
        self.__name = name

    def get_age(self):
        return self.__age

    def set_age(self, age):
        if age > 18:
            self.__age = age
        else:
            print("Age must be greater than 18")

# Usage
emp = Employee()
emp.set_name("John Doe")
emp.set_age(25)
print("Employee Name:", emp.get_name())
print("Employee Age:", emp.get_age())
```

### **Output:**
```
Employee Name: John Doe
Employee Age: 25
```

---

## **Encapsulation and Data Hiding**

Encapsulation helps **hide implementation details** while exposing only necessary methods.

### **Example: Hiding Implementation Details**

```python
class Account:
    def __init__(self, initial_balance):
        self.__balance = initial_balance

    def __validate_withdrawal(self, amount):
        return amount > 0 and amount <= self.__balance

    def withdraw(self, amount):
        if self.__validate_withdrawal(amount):
            self.__balance -= amount
            print(f"Withdrawal Successful: {amount}")
        else:
            print("Insufficient balance or invalid amount")

    def get_balance(self):
        return self.__balance

# Usage
my_account = Account(1000)
my_account.withdraw(300)
print("Remaining Balance:", my_account.get_balance())
```

### **Output:**
```
Withdrawal Successful: 300
Remaining Balance: 700
```

**Why Hide Data?**
- Prevents direct modification of important fields.
- Ensures data integrity by validating inputs.

---

## **Encapsulation in Real-World Applications**

Encapsulation is used in many real-world applications such as:
1. **Banking Systems** - Ensuring account details are private.
2. **Healthcare Applications** - Protecting patient records.
3. **E-Commerce Platforms** - Hiding payment processing details.

### **Example: Encapsulation in Payment Processing**

```python
class PaymentProcessor:
    def __init__(self, card_number, amount):
        self.__card_number = self.__mask_card_number(card_number)
        self.__amount = amount

    def __mask_card_number(self, card_number):
        return "****-****-****-" + card_number[-4:]

    def process_payment(self):
        print(f"Processing payment of {self.__amount} for card {self.__card_number}")

# Usage
payment = PaymentProcessor("1234567812345678", 250.00)
payment.process_payment()
```

### **Output:**
```
Processing payment of 250.0 for card ****-****-****-5678
```

**Why Use Encapsulation in Payment Processing?**
- Protects sensitive data (e.g., credit card numbers).
- Hides unnecessary details from users.
- Ensures secure transactions.