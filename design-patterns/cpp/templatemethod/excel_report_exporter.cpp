#include "excel_report_exporter.h"
#include <iostream>

void ExcelReportExporter::writeHeader(const ReportData& data) {
    std::cout << "Writing Excel header..." << std::endl;
    std::cout << "| ";
    for (const auto& header : data.getHeaders()) {
        std::cout << header << " | ";
    }
    std::cout << std::endl;
    std::cout << "|";
    for (size_t i = 0; i < data.getHeaders().size(); ++i) {
        std::cout << "---|";
    }
    std::cout << std::endl;
}

void ExcelReportExporter::writeDataRows(const ReportData& data) {
    std::cout << "Writing Excel data rows..." << std::endl;
    for (const auto& row : data.getRows()) {
        std::cout << "| ";
        for (const auto& header : data.getHeaders()) {
            const auto& value = row.at(header);
            std::visit([](const auto& v) { std::cout << v; }, value);
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
} 