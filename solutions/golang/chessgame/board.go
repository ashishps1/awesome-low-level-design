package chessgame

type Board struct {
	pieces [][]Piece
}

func NewBoard() *Board {
	board := &Board{
		pieces: make([][]Piece, 8),
	}
	for i := range board.pieces {
		board.pieces[i] = make([]Piece, 8)
	}
	board.initializeBoard()
	return board
}

func (b *Board) initializeBoard() {
	// Initialize white pieces
	b.pieces[0][0] = NewRook(White, 0, 0)
	b.pieces[0][1] = NewKnight(White, 0, 1)
	b.pieces[0][2] = NewBishop(White, 0, 2)
	b.pieces[0][3] = NewQueen(White, 0, 3)
	b.pieces[0][4] = NewKing(White, 0, 4)
	b.pieces[0][5] = NewBishop(White, 0, 5)
	b.pieces[0][6] = NewKnight(White, 0, 6)
	b.pieces[0][7] = NewRook(White, 0, 7)
	for i := 0; i < 8; i++ {
		b.pieces[1][i] = NewPawn(White, 1, i)
	}

	// Initialize black pieces
	b.pieces[7][0] = NewRook(Black, 7, 0)
	b.pieces[7][1] = NewKnight(Black, 7, 1)
	b.pieces[7][2] = NewBishop(Black, 7, 2)
	b.pieces[7][3] = NewQueen(Black, 7, 3)
	b.pieces[7][4] = NewKing(Black, 7, 4)
	b.pieces[7][5] = NewBishop(Black, 7, 5)
	b.pieces[7][6] = NewKnight(Black, 7, 6)
	b.pieces[7][7] = NewRook(Black, 7, 7)
	for i := 0; i < 8; i++ {
		b.pieces[6][i] = NewPawn(Black, 6, i)
	}
}

func (b *Board) GetPiece(row, col int) Piece {
	if row < 0 || row > 7 || col < 0 || col > 7 {
		return nil
	}
	return b.pieces[row][col]
}

func (b *Board) SetPiece(row, col int, piece Piece) {
	if row >= 0 && row < 8 && col >= 0 && col < 8 {
		b.pieces[row][col] = piece
	}
}

func (b *Board) IsValidMove(piece Piece, destRow, destCol int) bool {
	if piece == nil || destRow < 0 || destRow > 7 || destCol < 0 || destCol > 7 {
		return false
	}
	destPiece := b.GetPiece(destRow, destCol)
	return (destPiece == nil || destPiece.GetColor() != piece.GetColor()) &&
		piece.CanMove(b, destRow, destCol)
}

func (b *Board) IsCheckmate(color Color) bool {
	// TODO: Implement checkmate logic
	return false
}

func (b *Board) IsStalemate(color Color) bool {
	// TODO: Implement stalemate logic
	return false
}
