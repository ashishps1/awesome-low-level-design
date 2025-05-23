#pragma once
#include <string>
#include <vector>
#include <map>
#include <variant>

class ReportData {
public:
    std::vector<std::string> getHeaders() const;
    std::vector<std::map<std::string, std::variant<int, double, std::string>>> getRows() const;
}; 