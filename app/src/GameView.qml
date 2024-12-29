import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import linjesuxus.game
import linjesuxus.settingsProxy

Rectangle {
    color: Material.background
    property alias menuButton: menu.button
    property alias gameItem: game
    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: parent.width / 6
            Layout.maximumHeight: parent.width / 3
            Layout.preferredWidth: parent.width
            Image {
                id: gameStateImage
                source: "image://GameStatus/" + game.gameState
                Layout.fillHeight: true
                Layout.preferredWidth: height
            }
            Text {
                id: gameState
                text: game.gameState
                color: Material.foreground
                Layout.fillWidth: true
                height: parent.height
            }
        }
        RowLayout {
            spacing: 0
            Layout.minimumHeight: parent.width / 6
            Layout.maximumHeight: parent.width / 2
            IconButton {
                id: menu
                source: "/images/QTttMenu.svg"
            }
            IconButton {
                id: restart
                source: "/images/QTttRestart.svg"
                button.onReleased: game.restart()
            }
        }
        Game {
            id: game
            Layout.preferredWidth: parent.width
            Layout.maximumWidth: (parent.height - parent.width / 3) / ratio
            Layout.preferredHeight: Layout.preferredWidth * ratio
            Layout.maximumHeight: Layout.maximumWidth * ratio
            Layout.alignment: Qt.AlignHCenter
            property real ratio: fieldHeight / fieldWidth
        }
    }
}
