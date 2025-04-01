package carrentalsystem

type Customer struct {
	Name                 string
	ContactInfo          string
	DriversLicenseNumber string
}

func NewCustomer(name, contactInfo, driversLicenseNumber string) *Customer {
	return &Customer{
		Name:                 name,
		ContactInfo:          contactInfo,
		DriversLicenseNumber: driversLicenseNumber,
	}
}
