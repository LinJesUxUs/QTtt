import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import linjesuxus.game

Rectangle {
    id: root
    width: 300
    height: 480
    color: "gray"
    ColumnLayout {
        anchors.fill: root
        RowLayout {
            width: parent.width
            height: restart.height
            Button {
                id: restart
                text: "Restart"
                onPressed: game.restart()
            }
        }
        Text {
            id: gameState
            text: game.gameState
        }

        Game {
            id: game
            width: parent.width
            height: width
            // anchors {
            //     top: parent.top
            //     left: parent.left
            // }
        }
    }
}
