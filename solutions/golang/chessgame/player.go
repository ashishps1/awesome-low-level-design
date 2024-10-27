package chessgame

type Player struct {
	color Color
}

func NewPlayer(color Color) *Player {
	return &Player{color: color}
}

func (p *Player) MakeMove(board *Board, move *Move) error {
	if !board.IsValidMove(move.piece, move.destRow, move.destCol) {
		return NewInvalidMoveError("Invalid move!")
	}

	sourceRow := move.piece.GetRow()
	sourceCol := move.piece.GetCol()
	board.SetPiece(sourceRow, sourceCol, nil)
	board.SetPiece(move.destRow, move.destCol, move.piece)
	move.piece.SetPosition(move.destRow, move.destCol)
	return nil
}
