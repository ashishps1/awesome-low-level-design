package musicstreamingservice

type Artist struct {
	ID     string
	Name   string
	Albums []*Album
}
