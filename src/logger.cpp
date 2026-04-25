#include <GLEngine/logger.hpp>
#include <chrono>
#include <ctime>
#include <cctype>

// Static Data
const std::string gle::Logger::logColors[6] = {
    "#ededed",      // Comment
    "#8dc7f1",      // Output
    "#f1c48d",      // Warning
    "#f18d8d",      // Error
    "#a9f18d",      // Success
    "#9f8df1",      // Critical
};

const std::string gle::Logger::logTags[6] = {
    "Info    ",       // Comment
    "Output  ",       // Output
    "Warning ",       // Warning
    "Error   ",       // Error
    "Success ",       // Success
    "Critical",       // Critical
};

// Helpers


std::string GetColorCode(const std::string& hex) {
    // Fallback: default terminal color
    constexpr const char* fallback = "\x1b[0m";

    if (hex.size() != 7 || hex[0] != '#')
        return fallback;

    // Validate hex characters first
    for (size_t i = 1; i < 7; ++i)
    {
        if (!std::isxdigit(static_cast<unsigned char>(hex[i])))
            return fallback;
    }

    // Manual hex parsing (no stoi, no exceptions)
    auto hexToInt = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
        if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
        return 0;
    };

    int r = hexToInt(hex[1]) * 16 + hexToInt(hex[2]);
    int g = hexToInt(hex[3]) * 16 + hexToInt(hex[4]);
    int b = hexToInt(hex[5]) * 16 + hexToInt(hex[6]);

    return "\x1b[38;2;" +
           std::to_string(r) + ";" +
           std::to_string(g) + ";" +
           std::to_string(b) + "m";
}

std::string GetTimestamp() {
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t time = system_clock::to_time_t(now);

    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    char buffer[9]; // HH:MM:SS
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &localTime);

    return buffer;
}

void Print(const std::string& message, const std::string& tag, const std::string& color) {
    const std::string ansi = GetColorCode(color);
    const std::string reset = "\x1b[0m";

    std::cout
        << ansi
        << "[" << GetTimestamp() << "]"
        << "[" << tag << "] "
        << message
        << reset
        << std::endl;
}

// Main
void gle::Logger::Log(std::string message, LogType type) {
    Print(message, logTags[(unsigned int)type], logColors[(unsigned int)type]);
}

void gle::Logger::Log(std::string message, std::string tag, std::string color) {
    Print(message, tag, color);
}

void gle::Logger::LogCritical(std::string message, int errorCode) {
    // Message and close all
    Print(message, logTags[5], logColors[5]);
    exit(errorCode);
}