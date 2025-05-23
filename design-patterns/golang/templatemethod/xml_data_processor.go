package templatemethod

import "fmt"

type XMLDataProcessor struct{}

func (x *XMLDataProcessor) ReadData() {
	fmt.Println("Reading data from XML file...")
}

func (x *XMLDataProcessor) ProcessData() {
	fmt.Println("Processing XML data...")
}

func (x *XMLDataProcessor) SaveData() {
	fmt.Println("Saving processed data to XML file...")
}
