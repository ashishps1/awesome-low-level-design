#pragma once
#include "report_data.h"
#include <string>

class AbstractReportExporter {
public:
    virtual ~AbstractReportExporter() = default;
    
    // Template method
    void exportReport(const ReportData& data, const std::string& filePath);

protected:
    // Hook methods - optional for subclasses to override
    virtual void prepareData(const ReportData& data);
    virtual void openFile(const std::string& filePath);
    virtual void writeHeader(const ReportData& data) = 0;
    virtual void writeDataRows(const ReportData& data) = 0;
    virtual void writeFooter(const ReportData& data);
    virtual void closeFile(const std::string& filePath);
}; 