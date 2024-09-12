package main

import (
	"github.com/ashishps1/awesome-low-level-design/logging-framework/enum"
	"github.com/ashishps1/awesome-low-level-design/logging-framework/interfaces"
	"sync"
)

var (
	instance Logger
	once     sync.Once
)

type Logger struct {
	LogConfig *LogConfig
}

func GetInstance() *Logger {
	once.Do(func() {
		instance = Logger{LogConfig: &LogConfig{
			LogLevel:         enum.INFO,
			PublishBehaviour: &ConsoleLogPublish{},
		}}
	})
	return &instance
}

func (l *Logger) SetLogLevel(level enum.LogLevel) {
	l.LogConfig.SetLogLevel(level)
}

func (l *Logger) SetLogPublish(behaviour interfaces.LogPublish) {
	l.LogConfig.SetLogPublish(behaviour)
}

func (l *Logger) log(level enum.LogLevel, msg string) {
	if level.EnumIndex() >= l.LogConfig.LogLevel.EnumIndex() {
		log := NewLog(msg, level)
		l.LogConfig.PublishBehaviour.PublishLog(log.ToString())
	}
}
func (l *Logger) Info(msg string) {
	l.log(enum.INFO, msg)
}

func (l *Logger) Debug(msg string) {
	l.log(enum.DEBUG, msg)
}

func (l *Logger) Warning(msg string) {
	l.log(enum.WARNING, msg)
}

func (l *Logger) Error(msg string) {
	l.log(enum.ERROR, msg)
}

func (l *Logger) Fatal(msg string) {
	l.log(enum.FATAL, msg)
}
