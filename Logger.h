#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>

class Logger {
public:
    Logger(const std::string& writeFilename, const std::string& readFilename);
    ~Logger();

    void writeLog(const std::string& message);
    std::string readLog();

private:
    std::ofstream writeStream_;
    std::ifstream readStream_;
    mutable std::shared_mutex mutex_;
};
