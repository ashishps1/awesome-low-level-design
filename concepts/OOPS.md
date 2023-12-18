## Basics of Object-Oriented Programming (OOPS)

Object-Oriented Programming (OOP) is a fundamental programming paradigm used in software development, defined by its use of classes and objects. 

It’s built on four main principles: Inheritance, Polymorphism, Abstraction, and Encapsulation. 

These principles not only help in creating structured and reusable code but also make it easier to understand, maintain, and modify.

### Inheritance
nheritance allows one class to inherit the properties and methods of another class. It's a way to form a hierarchy between classes, promoting code reusability.
#### Example:
```java
class Vehicle {
    public void startEngine() {
        System.out.println("Engine started");
    }
}

class Car extends Vehicle {
    public void openTrunk() {
        System.out.println("Trunk opened");
    }
}

public class Main {
    public static void main(String[] args) {
        Car myCar = new Car();
        myCar.startEngine(); // Inherited method
        myCar.openTrunk(); // Own method
    }
}
```

In this Java example, `Car` inherits from `Vehicle`. 

Car can use the startEngine method from Vehicle, demonstrating inheritance.

### Polymorphism
Polymorphism allows objects of different classes to be treated as objects of a common superclass. It’s the ability of multiple object types to implement the same functionality, which can be achieved either by method overloading or method overriding.

#### Example:
```java
class Bird {
    public void sing() {
        System.out.println("Bird is singing");
    }
}

class Sparrow extends Bird {
    public void sing() {
        System.out.println("Sparrow is singing");
    }
}

public class Main {
    public static void main(String[] args) {
        Bird myBird = new Sparrow();
        myBird.sing(); // Outputs: Sparrow is singing
    }
}
```
Here, `Sparrow` overrides the sing method of `Bird`. Despite referring to Sparrow with a Bird reference, the overridden method in Sparrow is called.

### Abstraction
Abstraction is the concept of hiding complex implementation details and showing only the necessary features of an object. It can be achieved using abstract classes and interfaces.

#### Example:
```java
abstract class Animal {
    abstract void makeSound();

    public void eat() {
        System.out.println("Animal is eating");
    }
}

class Dog extends Animal {
    public void makeSound() {
        System.out.println("Bark");
    }
}

public class Main {
    public static void main(String[] args) {
        Animal myDog = new Dog();
        myDog.makeSound(); // Outputs: Bark
        myDog.eat(); // Inherited method
    }
}
```
`Animal` is an abstract class that provides a method `makeSound()`. 

`Dog` provides the specific implementation of this method.

### Encapsulation
Encapsulation is the technique of bundling data (variables) and methods that act on the data into a single unit, often called a class, and restricting access to some of the object’s components.

```java
class BankAccount {
    private double balance;

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    public void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }

    public double getBalance() {
        return balance;
    }
}

public class Main {
    public static void main(String[] args) {
        BankAccount account = new BankAccount();
        account.deposit(1000);
        account.withdraw(500);
        System.out.println("Balance: " + account.getBalance());
    }
}
```

In this example, the balance of the `BankAccount` is kept private. It can only be modified through the `deposit` and `withdraw` methods and read through the `getBalance` method, showcasing encapsulation.