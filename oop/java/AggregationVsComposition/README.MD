# Aggregation vs Composition in Java (Code-Focused)

In OOP, **Aggregation** and **Composition** both express "has-a" relationships, but they differ in **ownership**, **object lifecycle**, and **instantiation strategy**.

---

## 🔗 Aggregation — External Object Reference

### ✅ Key Code Characteristic:
> The referenced object is **passed from outside** and can exist independently.

```java
class Engine {
    String type;
    Engine(String type) {
        this.type = type;
    }
}

class Car {
    Engine engine; // Aggregation - reference passed from outside

    Car(Engine engine) {
        this.engine = engine;
    }

    void showEngineType() {
        System.out.println("Engine: " + engine.type);
    }
}

public class AggregationDemo {
    public static void main(String[] args) {
        Engine e1 = new Engine("V8");       // Created externally
        Car car1 = new Car(e1);             // Shared with car1

        Engine e2 = new Engine("V6");
        Car car2 = new Car(e2);             // Shared with car2

        car1.showEngineType(); // Engine: V8
        car2.showEngineType(); // Engine: V6
    }
}
```

**🧠 Key Point:**  
- `Car` does **not own** `Engine`.
- The same `Engine` can be reused across multiple `Car` objects.
- `Engine` can outlive or live independently of `Car`.

---

## 🔒 Composition — Object Created Internally

### ✅ Key Code Characteristic:
> The referenced object is **created inside** the constructor. It **cannot exist without the parent.**

```java
class Engine {
    String type;
    Engine(String type) {
        this.type = type;
    }
}

class Car {
    private Engine engine; // Composition - created inside

    Car(String engineType) {
        this.engine = new Engine(engineType); // tightly coupled
    }

    void showEngineType() {
        System.out.println("Engine: " + engine.type);
    }
}

public class CompositionDemo {
    public static void main(String[] args) {
        Car car = new Car("Electric");  // Engine is part of Car
        car.showEngineType();           // Engine: Electric
    }
}
```

**🧠 Key Point:**  
- `Car` **fully owns** `Engine`.
- `Engine` cannot be reused or accessed independently.
- Lifecycle of `Engine` is strictly bound to `Car`.

---

## 🔍 Code-Level Differences Summary

| Aspect                 | Aggregation                                | Composition                               |
|------------------------|---------------------------------------------|--------------------------------------------|
| Object creation        | Object is passed from outside               | Object is created internally               |
| Ownership              | Parent has a reference                      | Parent owns the object                     |
| Lifecycle dependency   | Child can live without parent               | Child dies with parent                     |
| Reusability            | Child can be reused by multiple parents     | Child is bound to one parent only          |
| Code style             | `this.child = child;`                       | `this.child = new Child();` or similar     |

---

## 💡 When to Use

- **Use Aggregation** when you want to share or reuse the same instance.
- **Use Composition** when you want a part to be a core, non-detachable component of the object.

---
