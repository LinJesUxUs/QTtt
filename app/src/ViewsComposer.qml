import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    width: 300
    height: 480
    visible: true
    color: "black"

    StackView {
        id: stack
        initialItem: initial
        anchors.fill: parent
    }

    Component {
        id: initial
        WelcomeView {
            startButton.onPressed: stack.push(game)
        }
    }

    Component {
        id: game
        GameView {
            menuButton.onPressed: stack.pop()
        }
    }
}
