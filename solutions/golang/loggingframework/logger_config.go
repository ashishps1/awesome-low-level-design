package loggingframework

type LoggerConfig struct {
	Level    LogLevel
	Appender LogAppender
}

func NewLoggerConfig(level LogLevel, appender LogAppender) *LoggerConfig {
	return &LoggerConfig{
		Level:    level,
		Appender: appender,
	}
}
