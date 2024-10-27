package cricinfo

type Ball struct {
	BallNumber int
	Bowler     string
	Batsman    string
	Result     string
}

func NewBall(ballNumber int, bowler, batsman, result string) *Ball {
	return &Ball{
		BallNumber: ballNumber,
		Bowler:     bowler,
		Batsman:    batsman,
		Result:     result,
	}
}
