package restaurantmanagementsystem

type Staff struct {
	ID            int
	Name          string
	Role          string
	ContactNumber string
}

func NewStaff(id int, name, role, contactNumber string) *Staff {
	return &Staff{
		ID:            id,
		Name:          name,
		Role:          role,
		ContactNumber: contactNumber,
	}
}
