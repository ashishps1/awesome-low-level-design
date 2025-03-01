# Encapsulation in C#

## Introduction

**Encapsulation** is one of the four fundamental principles of **Object-Oriented Programming (OOP)**. It is the practice of **bundling data (fields) and methods** that operate on that data into a single unit (**class**) while **restricting direct access** to the internal details.

Encapsulation in C# is achieved using:
1. **Access Modifiers** (`private`, `protected`, `public`)
2. **Properties (Getters and Setters)**
3. **Data Hiding**

Encapsulation helps in **data protection, modularity, and maintainability** of the code.

## **What is Encapsulation?**

Encapsulation means **wrapping** the data (fields) and code (methods) together into a single unit (class). It restricts direct access to some of an object's components, ensuring **data integrity and security**.

### **Key Benefits of Encapsulation**
- **Data Hiding**: Prevents direct access to sensitive data.
- **Increased Security**: Controls how data is accessed and modified.
- **Improved Code Maintainability**: Allows changes without affecting other parts of the code.
- **Better Modularity**: Organizes the code into logical components.

---

## **Encapsulation Using Access Modifiers in C#**

C# provides **access modifiers** to enforce encapsulation:
- **`private`**: Accessible only within the same class.
- **`protected`**: Accessible within the same class and derived (child) classes.
- **`public`**: Accessible from anywhere.
- **`internal`**: Accessible only within the same assembly.

### **Example: Encapsulation with Private Fields**
```csharp
using System;

class BankAccount
{
    private string accountHolder;
    private double balance;

    // Constructor
    public BankAccount(string accountHolder, double balance)
    {
        this.accountHolder = accountHolder;
        this.balance = balance;
    }

    // Getter method to access balance
    public double GetBalance()
    {
        return balance;
    }

    // Setter method to modify balance
    public void Deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            Console.WriteLine($"Deposited: {amount}");
        }
        else
        {
            Console.WriteLine("Invalid deposit amount");
        }
    }
}

class Program
{
    static void Main()
    {
        BankAccount account = new BankAccount("Alice", 1000);
        Console.WriteLine($"Current Balance: {account.GetBalance()}");
        account.Deposit(500);
        Console.WriteLine($"Updated Balance: {account.GetBalance()}");
    }
}
```

### **Output:**
```
Current Balance: 1000
Deposited: 500
Updated Balance: 1500
```

---

## **Encapsulation Using Properties (Getters and Setters)**

Encapsulation ensures that **data cannot be directly accessed** but must be retrieved or modified through **properties**.

### **Example: Properties in C#**
```csharp
using System;

class Employee
{
    private string name;
    private int age;

    // Property for Name
    public string Name
    {
        get { return name; }
        set { name = value; }
    }

    // Property for Age with validation
    public int Age
    {
        get { return age; }
        set
        {
            if (value > 18)
                age = value;
            else
                Console.WriteLine("Age must be greater than 18");
        }
    }
}

class Program
{
    static void Main()
    {
        Employee emp = new Employee();
        emp.Name = "John Doe";
        emp.Age = 25;
        Console.WriteLine($"Employee Name: {emp.Name}");
        Console.WriteLine($"Employee Age: {emp.Age}");
    }
}
```

### **Output:**
```
Employee Name: John Doe
Employee Age: 25
```

---

## **Encapsulation in Real-World Applications**

Encapsulation is used in many real-world applications such as:
1. **Banking Systems** - Ensuring account details are private.
2. **Healthcare Applications** - Protecting patient records.
3. **E-Commerce Platforms** - Hiding payment processing details.

### **Example: Encapsulation in Payment Processing**
```csharp
using System;

class PaymentProcessor
{
    private string cardNumber;
    private double amount;

    public PaymentProcessor(string cardNumber, double amount)
    {
        this.cardNumber = MaskCardNumber(cardNumber);
        this.amount = amount;
    }

    private string MaskCardNumber(string cardNumber)
    {
        return "****-****-****-" + cardNumber.Substring(cardNumber.Length - 4);
    }

    public void ProcessPayment()
    {
        Console.WriteLine($"Processing payment of {amount} for card {cardNumber}");
    }
}

class Program
{
    static void Main()
    {
        PaymentProcessor payment = new PaymentProcessor("1234567812345678", 250.00);
        payment.ProcessPayment();
    }
}
```

### **Output:**
```
Processing payment of 250 for card ****-****-****-5678
```