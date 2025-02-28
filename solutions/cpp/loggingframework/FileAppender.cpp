#include "FileAppender.hpp"

FileAppender::FileAppender(const std::string& filename) 
    : filename(filename) {
    file.open(filename, std::ios::app);
}

FileAppender::~FileAppender() {
    if (file.is_open()) {
        file.close();
    }
}

void FileAppender::append(const LogMessage& message) {
    if (file.is_open()) {
        file << message.getFormattedMessage() << std::endl;
    }
} 