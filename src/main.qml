import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import linjesuxus.game

Rectangle {
    id: root
    width: 300
    height: 480
    color: "gray"
    Game {
        width: parent.width
        height: width
        anchors {
            top: parent.top
            left: parent.left
        }
    }
}
