package linkedin

import "sync"

type Profile struct {
	ProfilePicture string
	Headline       string
	Summary        string
	Experiences    []*Experience
	Educations     []*Education
	Skills         []*Skill
	mu             sync.RWMutex
}

func NewProfile() *Profile {
	return &Profile{
		Experiences: make([]*Experience, 0),
		Educations:  make([]*Education, 0),
		Skills:      make([]*Skill, 0),
	}
}

func (p *Profile) SetSummary(summary string) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.Summary = summary
}

func (p *Profile) SetHeadline(headline string) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.Headline = headline
}
