import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

RowLayout {
    Layout.margins: spacing
    Layout.fillWidth: true
    property alias value: spinBox.value
    property alias text: text.text
    Text {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter
        id: text
        color: Material.foreground
    }
    SpinBox {
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignRight
        id: spinBox
        from: 1
        to: 20
    }
}
