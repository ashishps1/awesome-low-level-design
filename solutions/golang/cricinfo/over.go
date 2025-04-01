package cricinfo

type Over struct {
	OverNumber int
	Balls      []*Ball
}

func NewOver(overNumber int) *Over {
	return &Over{
		OverNumber: overNumber,
		Balls:      make([]*Ball, 0),
	}
}

func (o *Over) AddBall(ball *Ball) {
	o.Balls = append(o.Balls, ball)
}
