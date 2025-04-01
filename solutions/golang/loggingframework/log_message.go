package loggingframework

import (
	"fmt"
	"time"
)

type LogMessage struct {
	Level     LogLevel
	Message   string
	Timestamp int64
}

func NewLogMessage(level LogLevel, message string) *LogMessage {
	return &LogMessage{
		Level:     level,
		Message:   message,
		Timestamp: time.Now().UnixMilli(),
	}
}

func (m *LogMessage) String() string {
	return fmt.Sprintf("[%s] %d - %s", m.Level, m.Timestamp, m.Message)
}
