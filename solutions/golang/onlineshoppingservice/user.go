package onlineshopping

type User struct {
	ID       string
	Name     string
	Email    string
	Password string
	Orders   []Order
}

func NewUser(id, name, email, password string) *User {
	return &User{
		ID:       id,
		Name:     name,
		Email:    email,
		Password: password,
		Orders:   []Order{},
	}
}

func (u *User) AddOrder(order Order) {
	u.Orders = append(u.Orders, order)
}
