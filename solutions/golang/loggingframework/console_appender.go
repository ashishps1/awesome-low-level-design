package loggingframework

import "fmt"

type ConsoleAppender struct{}

func NewConsoleAppender() *ConsoleAppender {
	return &ConsoleAppender{}
}

func (a *ConsoleAppender) Append(message *LogMessage) error {
	fmt.Println(message.String())
	return nil
}
