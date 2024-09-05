package vehicles

type vehicleBase struct {
	RegistrationNo string
	VehicleType    VehicleType
}

type Vehicle interface {
	RegisNo() string
	Type() VehicleType
	Cost() int
}

func (v *vehicleBase) RegisNo() string {
	return v.RegistrationNo
}

func (v *vehicleBase) Type() VehicleType {
	return v.VehicleType
}
