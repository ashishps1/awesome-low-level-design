#include "pdf_report_exporter.h"
#include <iostream>

void PdfReportExporter::writeHeader(const ReportData& data) {
    std::cout << "Writing PDF header..." << std::endl;
    std::cout << "=== Report Header ===" << std::endl;
    for (const auto& header : data.getHeaders()) {
        std::cout << header << "\t";
    }
    std::cout << std::endl;
    std::cout << "===================" << std::endl;
}

void PdfReportExporter::writeDataRows(const ReportData& data) {
    std::cout << "Writing PDF data rows..." << std::endl;
    for (const auto& row : data.getRows()) {
        for (const auto& header : data.getHeaders()) {
            const auto& value = row.at(header);
            std::visit([](const auto& v) { std::cout << v; }, value);
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
} 