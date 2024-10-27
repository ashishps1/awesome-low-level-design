package coffeevendingmachine

import (
    "fmt"
    "sync"
)

type CoffeeMachine struct {
    coffeeMenu   []*Coffee
    ingredients  map[string]*Ingredient
    mu          sync.Mutex
}

var (
    instance *CoffeeMachine
    once     sync.Once
)

func GetCoffeeMachine() *CoffeeMachine {
    once.Do(func() {
        instance = &CoffeeMachine{
            coffeeMenu:  make([]*Coffee, 0),
            ingredients: make(map[string]*Ingredient),
        }
        instance.initializeIngredients()
        instance.initializeCoffeeMenu()
    })
    return instance
}

func (cm *CoffeeMachine) initializeIngredients() {
    cm.ingredients["Coffee"] = NewIngredient("Coffee", 10)
    cm.ingredients["Water"] = NewIngredient("Water", 10)
    cm.ingredients["Milk"] = NewIngredient("Milk", 10)
}

func (cm *CoffeeMachine) initializeCoffeeMenu() {
    // Espresso Recipe
    espressoRecipe := make(map[*Ingredient]int)
    espressoRecipe[cm.ingredients["Coffee"]] = 1
    espressoRecipe[cm.ingredients["Water"]] = 1
    cm.coffeeMenu = append(cm.coffeeMenu, NewCoffee("Espresso", 2.5, espressoRecipe))

    // Cappuccino Recipe
    cappuccinoRecipe := make(map[*Ingredient]int)
    cappuccinoRecipe[cm.ingredients["Coffee"]] = 1
    cappuccinoRecipe[cm.ingredients["Water"]] = 1
    cappuccinoRecipe[cm.ingredients["Milk"]] = 1
    cm.coffeeMenu = append(cm.coffeeMenu, NewCoffee("Cappuccino", 3.5, cappuccinoRecipe))

    // Latte Recipe
    latteRecipe := make(map[*Ingredient]int)
    latteRecipe[cm.ingredients["Coffee"]] = 1
    latteRecipe[cm.ingredients["Water"]] = 1
    latteRecipe[cm.ingredients["Milk"]] = 2
    cm.coffeeMenu = append(cm.coffeeMenu, NewCoffee("Latte", 4.0, latteRecipe))
}

func (cm *CoffeeMachine) DisplayMenu() {
    fmt.Println("Coffee Menu:")
    for _, coffee := range cm.coffeeMenu {
        fmt.Printf("%s - $%.2f\n", coffee.GetName(), coffee.GetPrice())
    }
}

func (cm *CoffeeMachine) SelectCoffee(coffeeName string) *Coffee {
    cm.mu.Lock()
    defer cm.mu.Unlock()

    for _, coffee := range cm.coffeeMenu {
        if coffee.GetName() == coffeeName {
            return coffee
        }
    }
    return nil
}

func (cm *CoffeeMachine) DispenseCoffee(coffee *Coffee, payment *Payment) error {
    cm.mu.Lock()
    defer cm.mu.Unlock()

    if coffee == nil {
        return fmt.Errorf("invalid coffee selection")
    }

    if payment.amount < coffee.GetPrice() {
        return fmt.Errorf("insufficient payment for %s", coffee.GetName())
    }

    if !cm.hasEnoughIngredients(coffee) {
        return fmt.Errorf("insufficient ingredients to make %s", coffee.GetName())
    }

    cm.updateIngredients(coffee)
    fmt.Printf("Dispensing %s...\n", coffee.GetName())

    change := payment.amount - coffee.GetPrice()
    if change > 0 {
        fmt.Printf("Please collect your change: $%.2f\n", change)
    }

    return nil
}

func (cm *CoffeeMachine) hasEnoughIngredients(coffee *Coffee) bool {
    for ingredient, requiredQuantity := range coffee.GetRecipe() {
        if ingredient.GetQuantity() < requiredQuantity {
            return false
        }
    }
    return true
}

func (cm *CoffeeMachine) updateIngredients(coffee *Coffee) {
    for ingredient, requiredQuantity := range coffee.GetRecipe() {
        ingredient.UpdateQuantity(-requiredQuantity)
        if ingredient.GetQuantity() < 3 {
            fmt.Printf("Low inventory alert: %s\n", ingredient.GetName())
        }
    }
}
