import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import conveyor.serialcom 1.0

Item {
    id: root
    Rectangle {
        id: start_button
        width: menu_panel.width / 10
        height: width / 2
        radius: height / 4
        color: "darkblue"
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 20
        }

        Text {
            id: icon_text
            text: "Start"
            anchors {
                centerIn: start_button
            }

            color: "white"
            font.bold: true
        }

        MouseArea {
            id: mouse_area
            anchors.fill: parent
            onPressed:
            {
                start_button.scale = 0.95
                start_button.color = "darkred"
                SerialComm.writeBytes()
            }
            onReleased:
            {
                start_button.scale = 1
                start_button.color = "darkblue"
            }
        }
    }

    Grid {
        anchors.centerIn: parent
        rows: 3
        columns: 4
        spacing: parent.width / 12

        Repeater {
            model: 12
            Button {
                text: "Button " + (index + 1)
                width: menu_panel.width / 10
                height: width / 2
                onClicked: {
                    SerialComm.writeBytes(index + 1)
                }
            }
        }
    }

}
