#include "date_time.h"

DateTime::DateTime(QObject *parent)
    : QObject{parent}
{
    updateCurrentTime();
}

void DateTime::updateCurrentTime() {
    currentTime = std::time(nullptr);
    localTime = std::localtime(&currentTime);
}

void DateTime::printCurrentDateTime() const {
    std::cout << "Current Date and Time: "
              << (localTime->tm_year + 1900) << '-'
              << (localTime->tm_mon + 1) << '-'
              << localTime->tm_mday << ' '
              << localTime->tm_hour << ':'
              << localTime->tm_min << ':'
              << localTime->tm_sec << std::endl;
}

void DateTime::printCurrentDate() const {
    std::cout << "Current Date: "
              << (localTime->tm_year + 1900) << '-'
              << (localTime->tm_mon + 1) << '-'
              << localTime->tm_mday << std::endl;
}

void DateTime::printCurrentTime() const {
    std::cout << "Current Time: "
              << localTime->tm_hour << ':'
              << localTime->tm_min << ':'
              << localTime->tm_sec << std::endl;
}
