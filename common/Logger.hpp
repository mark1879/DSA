#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include "Timestamp.hpp"

#define ENABLE_LOG 0

enum class LogLevel : std::uint8_t {
    kInfo,
    kError,
    kFatal,
    kDebug
};

class Logger {
public:
    static Logger& Instance() {
        static Logger logger;
        return logger;
    }

    void set_log_level(LogLevel level) {
        log_level_ = level;
    }

    void Log(std::string msg) {
#if ENABLE_LOG
        switch (log_level_)
        {
        case LogLevel::kInfo:
            std::cout << "[INFO]";
            break;
        case LogLevel::kError:
            std::cout << "[ERROR]";
            break;
        case LogLevel::kFatal:
            std::cout << "[FATAL]";
            break;
        case LogLevel::kDebug:
            std::cout << "[DEBUG]";
            break;
        default:
            break;
        }

        std::cout << TimeStamp::now().ToString() << " : " << msg << std::endl;
#endif
    }

private:
    LogLevel log_level_;
};

#define BUF_LEN 1024

#define LOG_INFO(log_msg_format, ...) \
    do { \
        Logger &logger = Logger::Instance(); \
        logger.set_log_level(LogLevel::kInfo); \
        char buf[BUF_LEN] = {0}; \
        snprintf(buf, BUF_LEN, log_msg_format, ##__VA_ARGS__); \
        logger.Log(buf); \
    } while(0) 

#define LOG_ERROR(log_msg_format, ...) \
    do \
    { \
        Logger &logger = Logger::Instance(); \
        logger.set_log_level(LogLevel::kError); \
        char buf[BUF_LEN] = {0}; \
        snprintf(buf, BUF_LEN, log_msg_format, ##__VA_ARGS__); \
        logger.Log(buf); \
    } while(0) 

#define LOG_FATAL(log_msg_format, ...) \
    do \
    { \
        Logger &logger = Logger::Instance(); \
        logger.set_log_level(LogLevel::kFatal); \
        char buf[BUF_LEN] = {0}; \
        snprintf(buf, BUF_LEN, log_msg_format, ##__VA_ARGS__); \
        logger.Log(buf); \
        exit(-1); \
    } while(0) 

#ifdef MUDEBUG
#define LOG_DEBUG(log_msg_format, ...) \
    do \
    { \
        Logger &logger = Logger::Instance(); \
        logger.set_log_level(LogLevel::kDebug); \
        char buf[BUF_LEN] = {0}; \
        snprintf(buf, BUF_LEN, log_msg_format, ##__VA_ARGS__); \
        logger.Log(buf); \
    } while(0) 
#else
    #define LOG_DEBUG(log_msg_format, ...)
#endif

#endif
