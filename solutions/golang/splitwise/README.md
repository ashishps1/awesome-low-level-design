# Splitwise - Low Level Design

## Requirements
1. Users can create accounts and manage profile information
2. Users can create groups and add other users to groups
3. Users can add expenses within a group, specifying amount, description, and participants
4. The system automatically splits expenses among participants based on their share
5. Users can view individual balances with other users and settle up
6. Support for different split methods: equal, percentage, and exact amounts
7. Users can view transaction history and group expenses
8. The system handles concurrent transactions with data consistency

## Architecture

```
API call (CreateExpense)
  |
  v
Facade (SplitwiseService)            <-- single entry point, holds the lock
  |
  +-- resolves paidBy user
  |
  +-- Factory (NewExpense)            <-- builds the expense
  |     |
  |     +-- Registry lookup           <-- picks the right SplitStrategy
  |     |
  |     +-- Strategy.Validate()       <-- strategy-specific validation
  |     |
  |     +-- resolves participant IDs
  |     |
  |     +-- Strategy.Compute()        <-- strategy-specific split math
  |
  +-- Group.AddExpense()              <-- membership validation
  |
  +-- updateBalances()                <-- balance ledger update
```

## Design Patterns

### 1. Strategy Pattern (`split.go`, `strategies.go`)

The `SplitStrategy` interface defines the contract for splitting algorithms:

```go
type SplitStrategy interface {
    Validate(amount float64, participants []Participant) error
    Compute(amount float64, users []*User, participants []Participant) []Split
}
```

Three concrete strategies implement this interface:
- **EqualStrategy** — divides the amount equally, ignores `Participant.Value`
- **PercentStrategy** — uses `Value` as percentage, validates they sum to 100
- **ExactStrategy** — uses `Value` as dollar amount, validates they sum to the total

### 2. Registry Pattern (`strategies.go`)

Strategies are registered in a map, decoupling strategy selection from expense creation:

```go
var strategyRegistry = map[ExpenseType]SplitStrategy{
    Equal:   NewEqualStrategy(),
    Percent: NewPercentStrategy(),
    Exact:   NewExactStrategy(),
}
```

Adding a new split type (e.g., shares-based) requires:
1. Implement `SplitStrategy`
2. Add one entry to `strategyRegistry`

No changes to `NewExpense`, the service, or any existing strategy.

### 3. Singleton Pattern (`service.go`)

`GetService()` uses `sync.Once` for a thread-safe single instance:

```go
var once sync.Once
func GetService() *SplitwiseService {
    once.Do(func() { instance = &SplitwiseService{...} })
    return instance
}
```

`ResetService()` enables clean test isolation by resetting the singleton.

### 4. Factory Method Pattern (`expense.go`)

`NewExpense` is a single factory that:
- Looks up the strategy from the registry
- Runs strategy-specific validation
- Resolves user IDs via a lookup function
- Delegates split computation to the strategy
- Returns a fully constructed `Expense`

Callers never construct splits or pick strategies manually.

### 5. Facade Pattern (`service.go`)

`SplitwiseService.CreateExpense()` is the single public entry point that orchestrates user lookup, expense creation, group membership validation, and balance updates behind one method call.

## File Structure

```
splitwise/
  ├── user.go           User model (ID, Name, Email)
  ├── split.go          Split struct + SplitStrategy interface
  ├── strategies.go     EqualStrategy, PercentStrategy, ExactStrategy + registry
  ├── expense.go        Expense model, Participant input, NewExpense factory
  ├── group.go          Group with membership management and validation
  ├── transaction.go    Transaction record for settlements
  ├── service.go        SplitwiseService (singleton, facade, concurrency)
  ├── demo.go           Working demo exercising all features
  └── splitwise_test.go Tests (equal/percent/exact, settlement, validation, concurrency)
```

## API Usage

All interaction goes through `SplitwiseService` using string IDs — ready for HTTP/gRPC:

```go
service := GetService()

// Register users
service.AddUser(NewUser("1", "Alice", "alice@example.com"))
service.AddUser(NewUser("2", "Bob", "bob@example.com"))

// Create group
group := NewGroup("g1", "Apartment")
group.AddMember(alice)
group.AddMember(bob)
service.AddGroup(group)

// Add expense — single uniform signature for all split types
service.CreateExpense("g1", "e1", 300, "Rent", "1", Equal, []Participant{
    {UserID: "1"},
    {UserID: "2"},
})

service.CreateExpense("g1", "e2", 200, "Groceries", "2", Percent, []Participant{
    {UserID: "1", Value: 60},
    {UserID: "2", Value: 40},
})

service.CreateExpense("g1", "e3", 150, "Dinner", "1", Exact, []Participant{
    {UserID: "1", Value: 50},
    {UserID: "2", Value: 100},
})

// Query balances
balance := service.GetBalance("1", "2")
allBalances := service.GetUserBalances("1")

// Settle up
tx, err := service.SettleBalance("2", "1")

// View history
transactions := service.GetTransactions()
```

## Concurrency

All public methods on `SplitwiseService` are protected by `sync.RWMutex`:
- **Read operations** (`GetUser`, `GetBalance`, `GetUserBalances`, `GetTransactions`) use `RLock` — multiple readers can proceed concurrently
- **Write operations** (`AddUser`, `AddGroup`, `CreateExpense`, `SettleBalance`) use `Lock` — exclusive access

This is verified by `TestConcurrentExpenses` which fires 100 goroutines adding expenses simultaneously and asserts correct final balances.

## Validation

The system validates at multiple levels:
- **Expense factory**: amount > 0, participants non-empty, user IDs exist
- **Strategy**: percent sums to 100, exact sums to total amount
- **Group**: payer and all participants must be group members

All errors are returned explicitly — no silent failures.

## Running

```bash
# Run demo
go run main.go

# Run tests
go test ./splitwise/ -v
```
