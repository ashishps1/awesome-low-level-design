#include "report_data.h"
#include "csv_report_exporter.h"
#include "pdf_report_exporter.h"
#include "excel_report_exporter.h"
#include <iostream>

int main() {
    ReportData data;

    // Export to CSV
    std::cout << "\nExporting to CSV..." << std::endl;
    CsvReportExporter csvExporter;
    csvExporter.exportReport(data, "report.csv");

    // Export to PDF
    std::cout << "\nExporting to PDF..." << std::endl;
    PdfReportExporter pdfExporter;
    pdfExporter.exportReport(data, "report.pdf");

    // Export to Excel
    std::cout << "\nExporting to Excel..." << std::endl;
    ExcelReportExporter excelExporter;
    excelExporter.exportReport(data, "report.xlsx");

    return 0;
} 