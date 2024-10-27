package chessgame

type Piece interface {
	CanMove(board *Board, destRow, destCol int) bool
	GetColor() Color
	GetRow() int
	GetCol() int
	SetPosition(row, col int)
}

type BasePiece struct {
	color Color
	row   int
	col   int
}

func (p *BasePiece) GetColor() Color { return p.color }
func (p *BasePiece) GetRow() int     { return p.row }
func (p *BasePiece) GetCol() int     { return p.col }
func (p *BasePiece) SetPosition(row, col int) {
	p.row = row
	p.col = col
}
