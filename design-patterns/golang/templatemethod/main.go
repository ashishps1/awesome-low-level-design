package templatemethod

func main() {
	csvProcessor := &CSVDataProcessor{}
	baseCSV := &BaseDataProcessor{Processor: csvProcessor}
	baseCSV.Process()

	xmlProcessor := &XMLDataProcessor{}
	baseXML := &BaseDataProcessor{Processor: xmlProcessor}
	baseXML.Process()
}
