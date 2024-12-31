import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Item {
    id: root
    Layout.fillHeight: true
    Layout.fillWidth: true
    property alias button: button
    property alias source: img.source
    IconImage {
        id: img
        height: Math.min(parent.width, parent.height)
        width: height
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: root
        antialiasing: true
        color: Material.foreground
        Button {
            id: button
            anchors.fill: img
            flat: true
            opacity: 0.5
        }
    }
}
