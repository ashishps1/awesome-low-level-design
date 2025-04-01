package musicstreamingservice

type Album struct {
	ID     string
	Title  string
	Artist string
	Songs  []*Song
}
