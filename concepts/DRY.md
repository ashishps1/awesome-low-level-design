## DRY Principle
In software development, the DRY (Don't Repeat Yourself) principle is a philosophy that, when adhered to, can significantly enhance the quality, maintainability, and scalability of code. 

This principle, at its core, is simple yet powerful: 

```"Every piece of knowledge must have a single, unambiguous, authoritative representation within a system."```

 The idea is to avoid redundancy in code, which often manifests in the form of repeated patterns, algorithms, or functions. 
 
 By eliminating these redundancies, developers ensure that every piece of knowledge or logic exists in only one place in their codebase.

### Why DRY principal is important?
- **Improved Maintainability:** Changes need to be made in only one place, reducing the risk of inconsistencies and bugs.
- **Enhanced Readability:** Code is cleaner and easier to understand when not cluttered with repetitions.
- **Easier Refactoring and Scaling:** With a single source of truth, it’s easier to modify and expand the system.

### Implementing DRY
#### Example 1: Avoiding Repetitive Code Blocks

Non-DRY Code:
```java
public void processDayData() {
    // process morning data
    extractData();
    transformData();
    loadData();
    
    // process afternoon data
    extractData();
    transformData();
    loadData();
    
    // process evening data
    extractData();
    transformData();
    loadData();
}
```

DRY Code:

```java
public void processDayData() {
    processData("morning");
    processData("afternoon");
    processData("evening");
}

private void processData(String partOfDay) {
    extractData(partOfDay);
    transformData(partOfDay);
    loadData(partOfDay);
}
```
In the DRY version, the repetitive tasks of data extraction, transformation, and loading are encapsulated within a single method, processData. This not only reduces the amount of code but also centralizes the logic for data processing.

#### Example 2: Using Functions to Encapsulate Logic
Non-DRY Code:
```python
total_price = price * quantity
if total_price > 500:
    discount = total_price * 0.1
    final_price = total_price - discount

# Later in the code
total_price = price2 * quantity2
if total_price > 500:
    discount = total_price * 0.1
    final_price = total_price - discount
```
DRY Code:
```python
def calculate_final_price(price, quantity):
    total_price = price * quantity
    discount = total_price * 0.1 if total_price > 500 else 0
    return total_price - discount

final_price = calculate_final_price(price, quantity)
final_price2 = calculate_final_price(price2, quantity2)
```
By creating a function calculate_final_price, we avoid repeating the discount calculation logic. Any changes to the discounting rules now only need to be made in one place.

### Tips for Practicing DRY
1. **Use Functions and Classes:** Encapsulate repeated logic in functions or classes.
1. **Leverage Inheritance and Composition:** In object-oriented programming, use inheritance and composition to reuse code.
1. **Employ Templates and Libraries:** Wherever possible, use templates or libraries that offer common functionalities.