package airlinemanagementsystem

type Aircraft struct {
	TailNumber string
	Model      string
	TotalSeats int
}

func NewAircraft(tailNumber, model string, totalSeats int) *Aircraft {
	return &Aircraft{
		TailNumber: tailNumber,
		Model:      model,
		TotalSeats: totalSeats,
	}
}
