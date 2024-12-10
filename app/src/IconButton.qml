import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Image {
    id: img
    Layout.fillHeight: true
    Layout.fillWidth: true
    fillMode: Image.PreserveAspectFit
    antialiasing: true
    property alias button: button
    Button {
        id: button
        anchors.fill: parent
        flat: true
        opacity: 0.5
    }
}
