#include "csv_report_exporter.h"
#include <iostream>
#include <sstream>

void CsvReportExporter::writeHeader(const ReportData& data) {
    std::cout << "Writing CSV header..." << std::endl;
    const auto& headers = data.getHeaders();
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << headers[i];
        if (i < headers.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

void CsvReportExporter::writeDataRows(const ReportData& data) {
    std::cout << "Writing CSV data rows..." << std::endl;
    for (const auto& row : data.getRows()) {
        for (const auto& header : data.getHeaders()) {
            const auto& value = row.at(header);
            std::visit([](const auto& v) { std::cout << v; }, value);
            if (&header != &data.getHeaders().back()) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
} 