import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import conveyor.serialcom 1.0

Item {
    id: root

    Grid {
        anchors.centerIn: parent
        rows: 3
        columns: 4
        spacing: parent.width / 10

        Repeater {
            model: 12
            Button {
                text: "Button " + (index + 1)
                width: menu_panel.width / 8
                height: width / 2
                onClicked: {
                    SerialComm.writeBytes(index + 1)
                }
            }
        }
    }

}
