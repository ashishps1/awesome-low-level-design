package main

import "github.com/ashishps1/awesome-low-level-design/logging-framework/enum"

func main() {
	logger := GetInstance()
	logger.Info("this is info")
	logger.Error("this is error")
	logger.Debug("this is debug") // shouldnt print

	logger.SetLogLevel(enum.WARNING)
	logger.Info("this info 2") // should not print
	logger.Warning("this is warning 2")
	logger.Error("this is error 2")

	logger.SetLogPublish(&FileLogPublish{FileName: "log.txt"})
	logger.Info("this info 2") // should not print
	logger.Warning("this is warning 3\n")
	logger.Error("this is error 4\n")
}
