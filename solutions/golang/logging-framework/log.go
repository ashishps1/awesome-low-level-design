package main

import (
	"fmt"
	"github.com/ashishps1/awesome-low-level-design/logging-framework/enum"
	"time"
)

type Log struct {
	Msg       string
	LogLevel  enum.LogLevel
	Timestamp time.Time
}

func NewLog(msg string, level enum.LogLevel) Log {
	return Log{
		Msg:       msg,
		LogLevel:  level,
		Timestamp: time.Now(),
	}
}

func (l Log) ToString() string {
	return fmt.Sprintf("[%s] [%s] %s", l.LogLevel.String(), l.Timestamp.String(), l.Msg)
}
