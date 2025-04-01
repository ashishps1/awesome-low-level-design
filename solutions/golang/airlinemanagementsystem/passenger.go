package airlinemanagementsystem

type Passenger struct {
	ID    string
	Name  string
	Email string
	Phone string
}

func NewPassenger(id, name, email, phone string) *Passenger {
	return &Passenger{
		ID:    id,
		Name:  name,
		Email: email,
		Phone: phone,
	}
}
