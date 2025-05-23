# Adapter Design Pattern in Python

## Problem Statement

The Adapter pattern allows incompatible interfaces to work together. It acts as a bridge between two incompatible interfaces by converting the interface of one class into another interface that clients expect.

---

## Core Components

### 1. Target Interface (PaymentProcessor)
```python
class PaymentProcessor(ABC):
    @abstractmethod
    def process_payment(self, amount: float, currency: str) -> None:
        pass
```

### 2. Adaptee (LegacyGateway)
```python
class LegacyGateway:
    def make_payment(self, currency: str, amount: float) -> None:
        # Legacy payment processing logic
        pass
```

### 3. Adapter (LegacyGatewayAdapter)
```python
class LegacyGatewayAdapter(PaymentProcessor):
    def __init__(self, legacy_gateway: LegacyGateway):
        self.legacy_gateway = legacy_gateway

    def process_payment(self, amount: float, currency: str) -> None:
        self.legacy_gateway.make_payment(currency, amount)
```

### 4. Client (CheckoutService)
```python
class CheckoutService:
    def __init__(self, payment_processor: PaymentProcessor):
        self.payment_processor = payment_processor

    def checkout(self, amount: float, currency: str) -> None:
        self.payment_processor.process_payment(amount, currency)
```

---

## Example Usage

```python
def main():
    # Using the in-house payment processor
    in_house_processor = InHousePaymentProcessor()
    checkout_service = CheckoutService(in_house_processor)
    checkout_service.checkout(100, "USD")

    # Using the legacy payment gateway through adapter
    legacy_processor = LegacyGatewayAdapter(LegacyGateway())
    checkout_service = CheckoutService(legacy_processor)
    checkout_service.checkout(100, "USD")
```

---

## Benefits

1. **Single Responsibility Principle:**
   - Separates the interface conversion logic from the business logic
   - Each class has a single responsibility

2. **Open/Closed Principle:**
   - New adapters can be added without modifying existing code
   - System remains open for extension but closed for modification

3. **Reusability:**
   - Existing classes can be reused with new interfaces
   - Reduces code duplication

4. **Flexibility:**
   - Multiple adapters can be created for different purposes
   - Easy to switch between different implementations

---

## When to Use

1. **When integrating incompatible interfaces:**
   - Working with legacy systems
   - Using third-party libraries
   - Migrating between different versions

2. **When creating a reusable class:**
   - The class needs to work with unrelated classes
   - The class needs to work with classes that don't have compatible interfaces

3. **When implementing multiple interfaces:**
   - A class needs to implement multiple interfaces
   - Different clients need different views of the same class

---

## Best Practices

1. **Keep it Simple:**
   - Adapters should be simple and focused
   - Avoid adding unnecessary functionality

2. **Documentation:**
   - Clearly document the purpose of the adapter
   - Explain the conversion logic

3. **Testing:**
   - Test the adapter thoroughly
   - Ensure it works with both the target and adaptee

4. **Error Handling:**
   - Handle conversion errors gracefully
   - Provide meaningful error messages

---

## Common Pitfalls

1. **Over-engineering:**
   - Creating adapters when not needed
   - Adding unnecessary complexity

2. **Tight Coupling:**
   - Creating dependencies between adapters
   - Making the system less flexible

3. **Performance Issues:**
   - Adding too many layers of adaptation
   - Impacting system performance

--- 