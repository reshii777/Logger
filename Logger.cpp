#include "Logger.h"

Logger::Logger(const std::string& writeFilename, const std::string& readFilename)
    : writeStream_(writeFilename, std::ios::app),
    readStream_(readFilename),
    mutex_() {
}

Logger::~Logger() {
    if (writeStream_.is_open()) {
        writeStream_.close();
    }
    if (readStream_.is_open()) {
        readStream_.close();
    }
}

void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    writeStream_ << message << std::endl;
}

std::string Logger::readLog() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    std::string message;
    if (std::getline(readStream_, message)) {
        return message;
    }
    return ""; // Возвращаем пустую строку, если больше нет данных для чтения
}
