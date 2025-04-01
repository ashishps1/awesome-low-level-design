package chessgame

type Move struct {
	piece   Piece
	destRow int
	destCol int
}

func NewMove(piece Piece, destRow, destCol int) *Move {
	return &Move{
		piece:   piece,
		destRow: destRow,
		destCol: destCol,
	}
}
