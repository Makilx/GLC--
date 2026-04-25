#pragma once

#include <GLEngine/pch.hpp>

namespace gle {
    enum class LogType : unsigned int {
        Comment = 0,
        Output = 1,
        Warning = 2,
        Error = 3,
        Success = 4,
    };

    class Logger {
      public:
        static void Log(std::string message, LogType type = LogType::Comment);
        static void Log(std::string message, std::string tag,
                        std::string color = "#ffff");
        static void LogCritical(std::string message, int errorCode = -1);

      private:
        const static std::string logColors[6];
        const static std::string logTags[6];
    };
} // namespace gle