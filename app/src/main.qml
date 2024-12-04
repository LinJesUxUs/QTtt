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
                color: "White"
                Layout.fillWidth: true
                height: parent.height
            }
        }
        RowLayout {
            spacing: 0
            Layout.minimumHeight: parent.width / 6
            Image {
                source: "/images/QTttMenu.svg"
                Layout.fillHeight: true
                Layout.fillWidth: true
                fillMode: Image.PreserveAspectFit
                Button {
                    anchors.fill: parent
                    flat: true
                    opacity: 0.5
                }
            }
            Image {
                source: "/images/QTttRestart.svg"
                Layout.fillHeight: true
                Layout.fillWidth: true
                fillMode: Image.PreserveAspectFit
                Button {
                    anchors.fill: parent
                    flat: true
                    opacity: 0.5
                    onPressed: game.restart()
                }
            }
        }
        Game {
            id: game
            Layout.preferredWidth: parent.width
            Layout.maximumWidth: parent.height - parent.width / 3
            Layout.preferredHeight: Layout.preferredWidth
            Layout.maximumHeight: Layout.maximumWidth
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
