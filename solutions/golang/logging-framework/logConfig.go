package main

import (
	"github.com/ashishps1/awesome-low-level-design/logging-framework/enum"
	"github.com/ashishps1/awesome-low-level-design/logging-framework/interfaces"
)

type LogConfig struct {
	LogLevel         enum.LogLevel
	PublishBehaviour interfaces.LogPublish
}

func (l *LogConfig) SetLogLevel(level enum.LogLevel) {
	l.LogLevel = level
}

func (l *LogConfig) SetLogPublish(behaviour interfaces.LogPublish) {
	l.PublishBehaviour = behaviour
}
