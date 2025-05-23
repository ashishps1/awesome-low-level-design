package templatemethod

import "fmt"

type CSVDataProcessor struct{}

func (c *CSVDataProcessor) ReadData() {
	fmt.Println("Reading data from CSV file...")
}

func (c *CSVDataProcessor) ProcessData() {
	fmt.Println("Processing CSV data...")
}

func (c *CSVDataProcessor) SaveData() {
	fmt.Println("Saving processed data to CSV file...")
}
