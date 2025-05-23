#include "report_data.h"

std::vector<std::string> ReportData::getHeaders() const {
    return {"ID", "Name", "Value"};
}

std::vector<std::map<std::string, std::variant<int, double, std::string>>> ReportData::getRows() const {
    return {
        {
            {"ID", 1},
            {"Name", "Item A"},
            {"Value", 100.0}
        },
        {
            {"ID", 2},
            {"Name", "Item B"},
            {"Value", 150.5}
        },
        {
            {"ID", 3},
            {"Name", "Item C"},
            {"Value", 75.25}
        }
    };
} 