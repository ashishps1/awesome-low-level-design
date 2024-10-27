package movieticketbookingsystem

type Movie struct {
	ID              string
	Title           string
	Description     string
	DurationMinutes int
}

func NewMovie(id, title, description string, durationMinutes int) *Movie {
	return &Movie{
		ID:              id,
		Title:           title,
		Description:     description,
		DurationMinutes: durationMinutes,
	}
}
