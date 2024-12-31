import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import linjesuxus.settingsProxy

Rectangle {
    id: root
    color: Material.background
    property alias button: startButton.button
    property alias settings: settings
    antialiasing: true
    ColumnLayout {
        anchors.fill: parent
        Layout.margins: spacing
        TextAndSpinBox {
            id: sbFieldWidth
            text: "Field width:"
            value: settings.fieldWidth
        }
        TextAndSpinBox {
            id: sbFieldHeight
            text: "Field height:"
            value: settings.fieldHeight
        }
        TextAndSpinBox {
            id: sbWinLength
            text: "Win length:"
            value: settings.winLength
        }
        TextAndSpinBox {
            id: sbPlayersCount
            text: "Players count:"
            value: settings.playersCount
        }
        TextAndSpinBox {
            id: sbFirstPlayer
            text: "First player:"
            value: settings.firstPlayer
        }
        IconButton {
            id: startButton
            source: "/images/QTttPlay.svg"
            Layout.preferredHeight: parent.width / 2
            Layout.preferredWidth: parent.width / 2
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
