#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "serial_comm.h"
#include "date_time.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    SerialComm* serial = new SerialComm(&app);
    QQmlApplicationEngine engine;
    DateTime* date_time = new DateTime(&app);
    qmlRegisterSingletonInstance("conveyor.datetime", 1, 0, "DateTime", date_time);
    qmlRegisterSingletonInstance("conveyor.serialcom", 1, 0, "SerialComm", serial);
    const QUrl url(u"qrc:/conveyor/qml/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
