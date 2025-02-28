#ifndef FILE_APPENDER_HPP
#define FILE_APPENDER_HPP

#include <string>
#include <fstream>
#include "LogAppender.hpp"

class FileAppender : public LogAppender {
private:
    std::string filename;
    std::ofstream file;

public:
    FileAppender(const std::string& filename);
    ~FileAppender();
    void append(const LogMessage& message) override;
};

#endif 