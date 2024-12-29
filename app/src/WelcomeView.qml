import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import linjesuxus.settingsProxy
import linjesuxus.game as GameItem

Rectangle {
    id: root
    color: "black"
    property alias button: startButton.button
    property alias settings: settings
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.margins: spacing
            Layout.fillWidth: true
            ColumnLayout {
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
                Text {
                    color: "white"
                    text: "Win length:"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }
                Text {
                    color: "white"
                    text: "Players count:"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }
                Text {
                    color: "white"
                    text: "First player:"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }
            }
            ColumnLayout {
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight
                SpinBox {
                    id: sbFieldWidth
                    // inputMethodComposing: Qt.platform.os === "android" ? false
                    from: 1
                    to: 20
                    value: settings.fieldWidth
                }
                SpinBox {
                    id: sbFieldHeight
                    from: 1
                    to: 20
                    value: settings.fieldHeight
                }
                SpinBox {
                    id: sbWinLength
                    from: 1
                    to: 20
                    value: settings.winLength
                }
                SpinBox {
                    id: sbPlayersCount
                    from: 1
                    to: 20
                    value: settings.playersCount
                }
                SpinBox {
                    id: sbFirstPlayer
                    from: 1
                    to: 20
                    value: settings.firstPlayer
                }
            }
        }
        IconButton {
            id: startButton
            source: "/images/QTttPlay.svg"
            Layout.fillWidth: true
            button.onPressed: {
                settings.fieldWidth = sbFieldWidth.value
                settings.fieldHeight = sbFieldHeight.value
                settings.winLength = sbWinLength.value
                settings.playersCount = sbPlayersCount.value
                settings.firstPlayer = sbFirstPlayer.value
            }
        }
        SettingsProxy {
            id: settings
        }
    }
}
