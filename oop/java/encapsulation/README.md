# Encapsulation in Java

## Introduction

**Encapsulation** is one of the four fundamental principles of Object-Oriented Programming (OOP). It is the practice of **bundling data (variables) and methods** that operate on that data into a single unit (class) while restricting direct access to the internal details.

Encapsulation in Java is achieved using:
1. **Access Modifiers** (`private`, `protected`, `public`)
2. **Getters and Setters**
3. **Data Hiding**

Encapsulation helps in **data protection, modularity, and maintainability** of the code.

---

## **What is Encapsulation?**

Encapsulation means **wrapping** the data (variables) and code (methods) together into a single unit (class). It restricts direct access to some of an object's components, which helps protect data integrity and prevents unintended modifications.

### **Key Benefits of Encapsulation**
- **Data Hiding**: Prevents direct access to sensitive data.
- **Increased Security**: Controls how data is accessed and modified.
- **Improved Code Maintainability**: Allows changes without affecting other parts of the code.
- **Better Modularity**: Organizes the code into logical components.

---

## **Encapsulation Using Access Modifiers**

Java provides **access modifiers** to enforce encapsulation:
- **`private`**: Accessible only within the same class.
- **`protected`**: Accessible within the same package and subclasses.
- **`public`**: Accessible from anywhere.

### **Example: Encapsulation with Private Variables**

```java
// Class with encapsulated data
class BankAccount {
    private String accountHolder;
    private double balance;

    // Constructor
    public BankAccount(String accountHolder, double balance) {
        this.accountHolder = accountHolder;
        this.balance = balance;
    }

    // Getter method to access balance
    public double getBalance() {
        return balance;
    }

    // Setter method to modify balance
    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            System.out.println("Deposited: " + amount);
        } else {
            System.out.println("Invalid deposit amount");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        BankAccount account = new BankAccount("Alice", 1000);
        System.out.println("Current Balance: " + account.getBalance());
        account.deposit(500);
        System.out.println("Updated Balance: " + account.getBalance());
    }
}
```

### **Output:**
```
Current Balance: 1000.0
Deposited: 500.0
Updated Balance: 1500.0
```

**Why Use Encapsulation?**
- Prevents unauthorized access to the data.
- Allows controlled modifications through methods.

---

## **Encapsulation Using Getters and Setters**

Encapsulation ensures that **data cannot be directly accessed** but must be retrieved or modified through methods.

### **Example: Getters and Setters in Java**

```java
class Employee {
    private String name;
    private int age;

    // Getter method
    public String getName() {
        return name;
    }

    // Setter method
    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        if (age > 18) {
            this.age = age;
        } else {
            System.out.println("Age must be greater than 18");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Employee emp = new Employee();
        emp.setName("John Doe");
        emp.setAge(25);
        System.out.println("Employee Name: " + emp.getName());
        System.out.println("Employee Age: " + emp.getAge());
    }
}
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

```java
class Account {
    private double balance;

    public Account(double initialBalance) {
        this.balance = initialBalance;
    }

    private boolean validateWithdrawal(double amount) {
        return amount > 0 && amount <= balance;
    }

    public void withdraw(double amount) {
        if (validateWithdrawal(amount)) {
            balance -= amount;
            System.out.println("Withdrawal Successful: " + amount);
        } else {
            System.out.println("Insufficient balance or invalid amount");
        }
    }

    public double getBalance() {
        return balance;
    }
}

public class Main {
    public static void main(String[] args) {
        Account myAccount = new Account(1000);
        myAccount.withdraw(300);
        System.out.println("Remaining Balance: " + myAccount.getBalance());
    }
}
```

### **Output:**
```
Withdrawal Successful: 300.0
Remaining Balance: 700.0
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

```java
class PaymentProcessor {
    private String cardNumber;
    private double amount;

    public PaymentProcessor(String cardNumber, double amount) {
        this.cardNumber = maskCardNumber(cardNumber);
        this.amount = amount;
    }

    private String maskCardNumber(String cardNumber) {
        return "****-****-****-" + cardNumber.substring(cardNumber.length() - 4);
    }

    public void processPayment() {
        System.out.println("Processing payment of " + amount + " for card " + cardNumber);
    }
}

public class Main {
    public static void main(String[] args) {
        PaymentProcessor payment = new PaymentProcessor("1234567812345678", 250.00);
        payment.processPayment();
    }
}
```

### **Output:**
```
Processing payment of 250.0 for card ****-****-****-5678
```

**Why Use Encapsulation in Payment Processing?**
- Protects sensitive data (e.g., credit card numbers).
- Hides unnecessary details from users.
- Ensures secure transactions.