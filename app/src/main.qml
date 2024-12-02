import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import linjesuxus.game

Rectangle {
    id: root
    color: "black"
    width: 300
    height: 480
    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 20
            Layout.preferredHeight: parent.height - parent.width * 1.5
            Layout.preferredWidth: parent.width
            Layout.alignment: Qt.AlignVCenter
            Image {
                id: gameStateImage
                source: game.gameStateImage.valueOf(QImage)
                Layout.preferredWidth: parent.width / 3
                Layout.preferredHeight: Layout.preferredWidth
                Layout.maximumHeight: Layout.preferredWidth
                Layout.maximumWidth: Layout.preferredWidth
            }
            Text {
                id: gameState
                text: game.gameState
                color: "White"
                Layout.maximumHeight: width / 3
                Layout.alignment: Qt.AlignCenter
            }
        }
        RowLayout {
            spacing: 0
            Layout.preferredHeight: width / 2
            Layout.maximumHeight: width / 2
            Layout.minimumHeight: 20
            Layout.alignment: Qt.AlignBottom
            Button {
                id: menu
                text: "Menu"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                id: restart
                text: "Restart"
                Layout.fillHeight: true
                Layout.fillWidth: true
                onPressed: game.restart()
            }
        }
        Game {
            id: game
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: Layout.preferredWidth
            Layout.alignment: Qt.AlignBottom
        }
    }
}
