package fooddeliveryservice

type Customer struct {
	ID    string
	Name  string
	Email string
	Phone string
}

func NewCustomer(id, name, email, phone string) *Customer {
	return &Customer{
		ID:    id,
		Name:  name,
		Email: email,
		Phone: phone,
	}
}
