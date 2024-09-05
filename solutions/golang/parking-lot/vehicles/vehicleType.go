package vehicles

type VehicleType int

const (
	CAR VehicleType = iota + 1
	TRUCK
	BIKE
)

func (v VehicleType) String() string {
	return [...]string{"Car", "Truck", "Bike"}[v-1]
}

func (v VehicleType) EnumIndex() int {
	return int(v)
}
