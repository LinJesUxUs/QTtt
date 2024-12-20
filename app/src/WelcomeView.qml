import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.settings

Rectangle {
    color: "black"
    property alias startButton: startButton.button
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.margins: spacing
            Layout.fillWidth: true
            ColumnLayout {
                // Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    color: "white"
                    text: "Field width:"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }
                Text {
                    color: "white"
                    text: "Field height:"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }
            }
            ColumnLayout {
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight
                SpinBox {
                    id: sbFieldWidth
                    from: 1
                    to: 20
                    // value: settings.gameFieldSize.width
                }
                SpinBox {
                    id: sbFieldHeight
                    from: 1
                    to: 20
                    // value: settings.gameFieldSize.height
                }
            }
        }

        IconButton {
            id: startButton
            source: "/images/QTttPlay.svg"
            Layout.fillWidth: true
        }
        Settings {
            id: settings
            category: "GameConfig"
            property alias fieldWidth: sbFieldWidth.value
            property alias fieldHeight: sbFieldHeight.value
        }
    }
}
