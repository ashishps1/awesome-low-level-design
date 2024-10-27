package hotelmanagement

type Guest struct {
	ID          string
	Name        string
	Email       string
	PhoneNumber string
}

func NewGuest(id, name, email, phoneNumber string) *Guest {
	return &Guest{
		ID:          id,
		Name:        name,
		Email:       email,
		PhoneNumber: phoneNumber,
	}
}
