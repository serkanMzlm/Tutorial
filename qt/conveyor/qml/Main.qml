import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Conveyor App")
    color: "gray"

    visibility: Window.FullScreen

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

    Rectangle {
        id: side_panel
        width: parent.width / 10
        height: parent.height - main_toolbar.height
        color: "lightgray"

        anchors {
            top: main_toolbar.bottom
            right: parent.right
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0
            Button {
                // text: "Home"
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/home.png"
                icon.width: 100
                icon.height: 100
            }
            Button {
                // text: "Warning"
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/warning.png"
                icon.width: 100
                icon.height: 100
            }
            Button {
                // text: "Settings"
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/settings.png"
                icon.width: 100
                icon.height: 100
            }
            Button {
                // text: "Services"
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/service.png"
                icon.width: 100
                icon.height: 100
            }
            Button {
                // text: "Reset"
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/reset.png"
                icon.width: 100
                icon.height: 100
            }
            Button {
                // text: "Start / Stop"
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/play.png"
                icon.width: 100
                icon.height: 100
                onClicked: {
                    icon.source = icon.source == "../assets/icons/play.png" ? "../assets/icons/pause.png" : "../assets/icons/play.png";
                }
            }
        }
    }
}
