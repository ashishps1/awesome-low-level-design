package chessgame

import "math"

type Pawn struct {
	BasePiece
}

func NewPawn(color Color, row, col int) *Pawn {
	return &Pawn{BasePiece{color, row, col}}
}

func (p *Pawn) CanMove(board *Board, destRow, destCol int) bool {
	rowDiff := destRow - p.row
	colDiff := math.Abs(float64(destCol - p.col))

	if p.color == White {
		return (rowDiff == 1 && colDiff == 0) ||
			(p.row == 1 && rowDiff == 2 && colDiff == 0) ||
			(rowDiff == 1 && colDiff == 1 && board.GetPiece(destRow, destCol) != nil)
	}
	return (rowDiff == -1 && colDiff == 0) ||
		(p.row == 6 && rowDiff == -2 && colDiff == 0) ||
		(rowDiff == -1 && colDiff == 1 && board.GetPiece(destRow, destCol) != nil)
}

type Rook struct {
	BasePiece
}

func NewRook(color Color, row, col int) *Rook {
	return &Rook{BasePiece{color, row, col}}
}

func (r *Rook) CanMove(board *Board, destRow, destCol int) bool {
	return r.row == destRow || r.col == destCol
}

type Knight struct {
	BasePiece
}

func NewKnight(color Color, row, col int) *Knight {
	return &Knight{BasePiece{color, row, col}}
}

func (k *Knight) CanMove(board *Board, destRow, destCol int) bool {
	rowDiff := math.Abs(float64(destRow - k.row))
	colDiff := math.Abs(float64(destCol - k.col))
	return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)
}

type Bishop struct {
	BasePiece
}

func NewBishop(color Color, row, col int) *Bishop {
	return &Bishop{BasePiece{color, row, col}}
}

func (b *Bishop) CanMove(board *Board, destRow, destCol int) bool {
	rowDiff := math.Abs(float64(destRow - b.row))
	colDiff := math.Abs(float64(destCol - b.col))
	return rowDiff == colDiff
}

type Queen struct {
	BasePiece
}

func NewQueen(color Color, row, col int) *Queen {
	return &Queen{BasePiece{color, row, col}}
}

func (q *Queen) CanMove(board *Board, destRow, destCol int) bool {
	rowDiff := math.Abs(float64(destRow - q.row))
	colDiff := math.Abs(float64(destCol - q.col))
	return (rowDiff == colDiff) || (q.row == destRow || q.col == destCol)
}

type King struct {
	BasePiece
}

func NewKing(color Color, row, col int) *King {
	return &King{BasePiece{color, row, col}}
}

func (k *King) CanMove(board *Board, destRow, destCol int) bool {
	rowDiff := math.Abs(float64(destRow - k.row))
	colDiff := math.Abs(float64(destCol - k.col))
	return rowDiff <= 1 && colDiff <= 1
}
