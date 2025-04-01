# Encapsulation in Golang

## Introduction

**Encapsulation** is one of the four fundamental principles of Object-Oriented Programming (OOP). It is the practice of **bundling data (variables) and methods** that operate on that data into a single unit (struct) while restricting direct access to the internal details.

Encapsulation in Golang is achieved using:
1. **Exported and Unexported Fields (Visibility Control)**
2. **Getters and Setters (Methods for Data Access)**
3. **Data Hiding**

Encapsulation helps in **data protection, modularity, and maintainability** of the code.

## **What is Encapsulation?**

Encapsulation means **wrapping** the data (fields) and code (methods) together into a single unit (struct). It restricts direct access to some of an object's components, which helps protect data integrity and prevents unintended modifications.

### **Key Benefits of Encapsulation**
- **Data Hiding**: Prevents direct access to sensitive data.
- **Increased Security**: Controls how data is accessed and modified.
- **Improved Code Maintainability**: Allows changes without affecting other parts of the code.
- **Better Modularity**: Organizes the code into logical components.

---

## **Encapsulation Using Exported and Unexported Fields**

Golang does not have traditional access modifiers like `private`, `protected`, or `public`. Instead, it uses **capitalization** to determine visibility:
- **Exported fields (Public)**: Fields that start with an **uppercase letter** can be accessed outside the package.
- **Unexported fields (Private)**: Fields that start with a **lowercase letter** are only accessible within the same package.

### **Example: Encapsulation with Unexported Fields**

```go
package main

import (
    "fmt"
)

// BankAccount struct with encapsulated data
type BankAccount struct {
    accountHolder string  // Unexported field (private)
    balance       float64 // Unexported field (private)
}

// Constructor function to initialize BankAccount
func NewBankAccount(holder string, balance float64) *BankAccount {
    return &BankAccount{accountHolder: holder, balance: balance}
}

// Getter method to access balance
func (b *BankAccount) GetBalance() float64 {
    return b.balance
}

// Setter method to modify balance
func (b *BankAccount) Deposit(amount float64) {
    if amount > 0 {
        b.balance += amount
        fmt.Println("Deposited:", amount)
    } else {
        fmt.Println("Invalid deposit amount")
    }
}

func main() {
    account := NewBankAccount("Alice", 1000)
    fmt.Println("Current Balance:", account.GetBalance())
    account.Deposit(500)
    fmt.Println("Updated Balance:", account.GetBalance())
}
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

### **Example: Getters and Setters in Golang**

```go
package main

import (
    "fmt"
)

// Employee struct with private fields
type Employee struct {
    name string
    age  int
}

// Getter for name
func (e *Employee) GetName() string {
    return e.name
}

// Setter for name
func (e *Employee) SetName(name string) {
    e.name = name
}

// Getter for age
func (e *Employee) GetAge() int {
    return e.age
}

// Setter for age with validation
func (e *Employee) SetAge(age int) {
    if age > 18 {
        e.age = age
    } else {
        fmt.Println("Age must be greater than 18")
    }
}

func main() {
    emp := Employee{}
    emp.SetName("John Doe")
    emp.SetAge(25)
    fmt.Println("Employee Name:", emp.GetName())
    fmt.Println("Employee Age:", emp.GetAge())
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

```go
package main

import (
    "fmt"
)

// Account struct with private balance
type Account struct {
    balance float64
}

// Constructor function
func NewAccount(initialBalance float64) *Account {
    return &Account{balance: initialBalance}
}

// Private method for withdrawal validation
func (a *Account) validateWithdrawal(amount float64) bool {
    return amount > 0 && amount <= a.balance
}

// Public method to withdraw
func (a *Account) Withdraw(amount float64) {
    if a.validateWithdrawal(amount) {
        a.balance -= amount
        fmt.Println("Withdrawal Successful:", amount)
    } else {
        fmt.Println("Insufficient balance or invalid amount")
    }
}

// Getter for balance
func (a *Account) GetBalance() float64 {
    return a.balance
}

func main() {
    myAccount := NewAccount(1000)
    myAccount.Withdraw(300)
    fmt.Println("Remaining Balance:", myAccount.GetBalance())
}
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

```go
package main

import (
    "fmt"
    "strings"
)

// PaymentProcessor struct
type PaymentProcessor struct {
    cardNumber string
    amount     float64
}

// Constructor function
func NewPaymentProcessor(cardNumber string, amount float64) *PaymentProcessor {
    return &PaymentProcessor{cardNumber: maskCardNumber(cardNumber), amount: amount}
}

// Private function to mask card number
func maskCardNumber(cardNumber string) string {
    return "****-****-****-" + cardNumber[len(cardNumber)-4:]
}

// Public method to process payment
func (p *PaymentProcessor) ProcessPayment() {
    fmt.Println("Processing payment of", p.amount, "for card", p.cardNumber)
}

func main() {
    payment := NewPaymentProcessor("1234567812345678", 250.00)
    payment.ProcessPayment()
}
```

### **Output:**
```
Processing payment of 250 for card ****-****-****-5678
```

**Why Use Encapsulation in Payment Processing?**
- Protects sensitive data (e.g., credit card numbers).
- Hides unnecessary details from users.
- Ensures secure transactions.