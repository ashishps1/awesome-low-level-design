package enums

type Ingredient int

const (
	MILK Ingredient = iota + 1
	SUGAR
	COFFEE
)

func (i Ingredient) String() string {
	return [...]string{"MILK", "SUGAR", "COFFEE"}[i-1]
}
