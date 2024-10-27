package loggingframework

type LogAppender interface {
	Append(message *LogMessage) error
}
