package main

import (
	"fmt"
	"os"
)

type ConsoleLogPublish struct {
}

func (c *ConsoleLogPublish) PublishLog(msg string) {
	fmt.Println(msg)
}

type FileLogPublish struct {
	FileName string
}

func (f *FileLogPublish) PublishLog(msg string) {
	// Open file in append mode
	file, err := os.OpenFile(f.FileName, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error opening the file:", err)
		return
	}
	defer file.Close()

	// Write content to the file
	_, err = file.WriteString(msg)
	if err != nil {
		fmt.Println("Error writing to the file:", err)
		return
	}

	fmt.Println("Log appended to the file successfully.")
}
