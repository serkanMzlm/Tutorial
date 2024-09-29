import QtQuick 2.15
import QtQuick.Window 2.15
import MainToolbar

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Conveyor App")
    color: "gray"

    //visibility: Window.FullScreen

    property color main_toolbar_base_color: "white"

    Rectangle {
        id: main_toolbar
        color: main_toolbar_base_color
        height: Math.max(parent.width * 0.03, parent.height * 0.03)
        width: parent.width

        anchors {
            top: parent.top
            left: parent.left
        }

        Rectangle{
            id: exit_rectangle
            height: parent.height * 0.75
            width: height
            radius: height / 2

            color: "red"
            anchors {
                right: parent.right
                rightMargin: parent.height * 0.125
                verticalCenter: parent.verticalCenter
            }

            Text {
                text: "X"
                font.pixelSize: Math.max(parent.width * 0.75, parent.height * 0.75)
                color: "white"
                anchors.centerIn: parent
                font.bold: true
            }

            MouseArea {
                id: exit
                anchors.fill: parent
                hoverEnabled: true
                onClicked:  Qt.quit()
            }

        }
    }
}
