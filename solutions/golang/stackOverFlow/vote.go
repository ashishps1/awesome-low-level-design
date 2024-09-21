package main

type Vote struct {
	Value int
}

func NewVote(value int) Vote {
	return Vote{
		Value: value,
	}
}
