package loggingframework

import (
	"fmt"
)

func Run() {
	logger := GetLogger()

	// Logging with default configuration
	logger.Info("This is an information message")
	logger.Warning("This is a warning message")
	logger.Error("This is an error message")

	// Changing log level and appender
	fileAppender := NewFileAppender("app.log")
	config := NewLoggerConfig(LogLevelDebug, fileAppender)
	logger.SetConfig(config)

	if err := logger.Debug("This is a debug message"); err != nil {
		fmt.Printf("Error logging debug message: %v\n", err)
	}

	if err := logger.Info("This is an information message"); err != nil {
		fmt.Printf("Error logging info message: %v\n", err)
	}
}
