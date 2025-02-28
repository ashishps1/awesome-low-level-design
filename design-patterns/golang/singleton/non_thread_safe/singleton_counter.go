package non_thread_safe

type Singleton interface {
	AddOne() int
}

type singleton struct {
	// to store the counter variable
	count int
}

var instance *singleton

func GetInstance() Singleton {
	if instance == nil {
		instance = &singleton{}
	}
	return instance
}

func (s *singleton) AddOne() int {
	return 0
}
