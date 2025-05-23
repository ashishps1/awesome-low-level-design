package templatemethod

import "fmt"

// DataProcessor defines the interface for steps
// and provides the template method Process
// (Go doesn't have abstract classes, so we use interface + embedding)
type DataProcessor interface {
	ReadData()
	ProcessData()
	SaveData()
}

type BaseDataProcessor struct {
	Processor DataProcessor
}

func (b *BaseDataProcessor) Process() {
	b.Processor.ReadData()
	b.Processor.ProcessData()
	b.Processor.SaveData()
	fmt.Println("Data processing completed.")
}
