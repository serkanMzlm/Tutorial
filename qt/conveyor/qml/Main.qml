import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: root
    visible: true
    title: qsTr("Conveyor App")
    color: "gray"

    visibility: Window.FullScreen

    property color main_toolbar_base_color: "white"
    property int image_text_dist: 10
    property int icon_size: 80
    property bool buton_highlighted : true

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
            spacing: 1

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/home.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    text: "Home"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/warning.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    text: "Alarms"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/settings.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    text: "Settings"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/service.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    text: "Service"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/reset.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    text: "Reset"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/play.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    id: start_stop_text
                    text: "Start"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
                onClicked: {
                    icon.source = icon.source == "../assets/icons/play.png" ? "../assets/icons/pause.png" : "../assets/icons/play.png";
                    start_stop_text.text = icon.source == "../assets/icons/play.png" ? "Start" : "Stop";
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                icon.source: "../assets/icons/test.png"
                icon.width: icon_size
                icon.height: icon_size
                highlighted: buton_highlighted
                Text {
                    id: test_button_text
                    text: "Test Mode"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: image_text_dist
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.bold: true
                }
            }
        }
    }
/**
    Rectangle{
        id: test_button
        width: 50
        height: 50
        color: "blue"
        anchors{
            right: side_panel.left
            bottom: parent.bottom
        }
    }*/
}
