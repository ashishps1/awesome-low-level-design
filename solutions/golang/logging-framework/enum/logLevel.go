package enum

type LogLevel int

const (
	DEBUG LogLevel = iota + 1
	INFO
	WARNING
	ERROR
	FATAL
)

func (l LogLevel) String() string {
	return [...]string{"info", "debug", "warning", "error", "fatal"}[l-1]
}

func (l LogLevel) EnumIndex() int {
	return int(l)
}
