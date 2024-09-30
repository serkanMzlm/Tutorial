#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <QObject>
#include <ctime>
#include <iostream>

class DateTime : public QObject
{
    Q_OBJECT
public:
    explicit DateTime(QObject *parent = nullptr);
    void printCurrentDateTime() const;
    void printCurrentDate() const;
    void printCurrentTime() const;
private:
    std::time_t currentTime;
    std::tm* localTime;
    void updateCurrentTime();
};

#endif // DATE_TIME_H
