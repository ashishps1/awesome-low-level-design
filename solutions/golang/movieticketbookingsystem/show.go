package movieticketbookingsystem

import (
	"sync"
	"time"
)

type Show struct {
	ID        string
	Movie     *Movie
	Theater   *Theater
	StartTime time.Time
	EndTime   time.Time
	Seats     map[string]*Seat
	mu        sync.RWMutex
}

func NewShow(id string, movie *Movie, theater *Theater, startTime, endTime time.Time, seats map[string]*Seat) *Show {
	return &Show{
		ID:        id,
		Movie:     movie,
		Theater:   theater,
		StartTime: startTime,
		EndTime:   endTime,
		Seats:     seats,
	}
}
