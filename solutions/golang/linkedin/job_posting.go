package linkedin

import "time"

type JobPosting struct {
	ID           string
	Title        string
	Description  string
	Requirements []string
	Location     string
	PostDate     time.Time
}

func NewJobPosting(id, title, description string, requirements []string, location string) *JobPosting {
	return &JobPosting{
		ID:           id,
		Title:        title,
		Description:  description,
		Requirements: requirements,
		Location:     location,
		PostDate:     time.Now(),
	}
}
