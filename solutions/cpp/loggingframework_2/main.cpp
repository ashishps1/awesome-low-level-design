// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class LogMessage;
class LogAppender;
class ConsoleAppender;
class FileAppender;
class Logger;

// ===== LogLevel.hpp =====
enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

// Helper function to convert LogLevel to string
inline string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

// ===== LogMessage.hpp =====
class LogMessage {
private:
    LogLevel level;
    string message;
    string timestamp;
    string source;

public:
    LogMessage(LogLevel level, const string& message, 
               const string& source);
    
    LogLevel getLevel() const;
    string getMessage() const;
    string getTimestamp() const;
    string getSource() const;
    string getFormattedMessage() const;
};

// ===== LogAppender.hpp =====
class LogAppender {
public:
    virtual ~LogAppender() = default;
    virtual void append(const LogMessage& message) = 0;
};

// ===== ConsoleAppender.hpp =====
class ConsoleAppender : public LogAppender {
public:
    void append(const LogMessage& message) override;
};

// ===== FileAppender.hpp =====
class FileAppender : public LogAppender {
private:
    string filename;
    ofstream file;

public:
    FileAppender(const string& filename);
    ~FileAppender();
    void append(const LogMessage& message) override;
};

// ===== Logger.hpp =====
class Logger {
private:
    string name;
    LogLevel minLevel;
    vector<shared_ptr<LogAppender>> appenders;

public:
    Logger(const string& name, LogLevel minLevel = LogLevel::INFO);
    
    void addAppender(shared_ptr<LogAppender> appender);
    void setMinLevel(LogLevel level);
    
    void log(LogLevel level, const string& message);
    void trace(const string& message);
    void debug(const string& message);
    void info(const string& message);
    void warn(const string& message);
    void error(const string& message);
    void fatal(const string& message);

private:
    bool isLevelEnabled(LogLevel level) const;
};

// ===== ConsoleAppender.cpp =====
void ConsoleAppender::append(const LogMessage& message) {
    cout << message.getFormattedMessage() << endl;
} 

// ===== FileAppender.cpp =====
FileAppender::FileAppender(const string& filename) 
    : filename(filename) {
    file.open(filename, ios::app);
}

FileAppender::~FileAppender() {
    if (file.is_open()) {
        file.close();
    }
}

void FileAppender::append(const LogMessage& message) {
    if (file.is_open()) {
        file << message.getFormattedMessage() << endl;
    }
} 

// ===== LogMessage.cpp =====
LogMessage::LogMessage(LogLevel level, const string& message, 
                      const string& source)
    : level(level), message(message), source(source) {
    // Get current timestamp
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    timestamp = oss.str();
}

LogLevel LogMessage::getLevel() const { return level; }
string LogMessage::getMessage() const { return message; }
string LogMessage::getTimestamp() const { return timestamp; }
string LogMessage::getSource() const { return source; }

string LogMessage::getFormattedMessage() const {
    ostringstream oss;
    oss << "[" << timestamp << "] "
        << "[" << logLevelToString(level) << "] "
        << "[" << source << "] "
        << message;
    return oss.str();
} 

// ===== Logger.cpp =====
Logger::Logger(const string& name, LogLevel minLevel)
    : name(name), minLevel(minLevel) {}

void Logger::addAppender(shared_ptr<LogAppender> appender) {
    appenders.push_back(appender);
}

void Logger::setMinLevel(LogLevel level) {
    minLevel = level;
}

bool Logger::isLevelEnabled(LogLevel level) const {
    return static_cast<int>(level) >= static_cast<int>(minLevel);
}

void Logger::log(LogLevel level, const string& message) {
    if (!isLevelEnabled(level)) return;
    
    LogMessage logMessage(level, message, name);
    for (const auto& appender : appenders) {
        appender->append(logMessage);
    }
}

void Logger::trace(const string& message) {
    log(LogLevel::TRACE, message);
}

void Logger::debug(const string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const string& message) {
    log(LogLevel::WARN, message);
}

void Logger::error(const string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::fatal(const string& message) {
    log(LogLevel::FATAL, message);
} 

// ===== LoggingDemo.cpp =====
int main() {
    // Create logger
    Logger logger("MyApp");
    
    // Add console appender
    auto consoleAppender = make_shared<ConsoleAppender>();
    logger.addAppender(consoleAppender);
    
    // Add file appender
    auto fileAppender = make_shared<FileAppender>("app.log");
    logger.addAppender(fileAppender);
    
    // Log messages at different levels
    logger.trace("This is a trace message");  // Won't be logged (below INFO)
    logger.debug("This is a debug message");  // Won't be logged (below INFO)
    logger.info("Application started");
    logger.warn("This is a warning message");
    logger.error("An error occurred");
    logger.fatal("Fatal error: application shutting down");
    
    // Change minimum log level
    logger.setMinLevel(LogLevel::DEBUG);
    logger.debug("Now debug messages will be logged");
    
    return 0;
} 

