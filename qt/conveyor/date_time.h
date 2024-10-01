#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <ctime>
#include <iostream>

class DateTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString calender READ calender WRITE setCalender NOTIFY calenderChanged FINAL)
public:
    explicit DateTime(QObject *parent = nullptr);
    ~DateTime();
    void printCurrentDateTime() const;
    void printCurrentDate() const;
    void printCurrentTime() const;
    void setFormattedDateTime();
    QString calender() const;
    void setCalender(const QString &newCalender);

signals:
    void calenderChanged();

private:
    std::time_t currentTime;
    std::tm* localTime;
    void updateCurrentTime();
    QTimer *timer;
    QString m_calender;
};

#endif // DATE_TIME_H
