package atm

type Card struct {
	CardNumber string
	PIN        string
}

func NewCard(cardNumber, pin string) *Card {
	return &Card{
		CardNumber: cardNumber,
		PIN:        pin,
	}
}
