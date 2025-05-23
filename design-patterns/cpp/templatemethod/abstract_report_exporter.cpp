#include "abstract_report_exporter.h"
#include <iostream>

void AbstractReportExporter::exportReport(const ReportData& data, const std::string& filePath) {
    prepareData(data);
    openFile(filePath);
    writeHeader(data);
    writeDataRows(data);
    writeFooter(data);
    closeFile(filePath);
    std::cout << "Report exported to " << filePath << std::endl;
}

void AbstractReportExporter::prepareData(const ReportData& data) {
    std::cout << "Preparing report data..." << std::endl;
}

void AbstractReportExporter::openFile(const std::string& filePath) {
    std::cout << "Opening file: " << filePath << std::endl;
}

void AbstractReportExporter::writeFooter(const ReportData& data) {
    std::cout << "Writing footer..." << std::endl;
}

void AbstractReportExporter::closeFile(const std::string& filePath) {
    std::cout << "Closing file: " << filePath << std::endl;
} 