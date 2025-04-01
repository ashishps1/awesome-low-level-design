package cricinfo

type Team struct {
	ID      string
	Name    string
	Players []*Player
}

func NewTeam(id, name string, players []*Player) *Team {
	return &Team{
		ID:      id,
		Name:    name,
		Players: players,
	}
}
