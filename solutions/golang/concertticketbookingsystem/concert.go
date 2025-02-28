package concertbookingsystem

import "time"

type Concert struct {
	ID       string
	Artist   string
	Venue    string
	DateTime time.Time
	Seats    []*Seat
}

func NewConcert(id, artist, venue string, dateTime time.Time, seats []*Seat) *Concert {
	return &Concert{
		ID:       id,
		Artist:   artist,
		Venue:    venue,
		DateTime: dateTime,
		Seats:    seats,
	}
}
