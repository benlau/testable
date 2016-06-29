import QtQuick 2.0
import QtQuick.Window 2.0

Window {

    width: 480
    height: 640

    visible: true

    Text {
        id: label
        objectName: "label"
        width: 50
        height: 60
        anchors.centerIn: parent
        text: "Label"
        font.pixelSize: 36
    }

}
