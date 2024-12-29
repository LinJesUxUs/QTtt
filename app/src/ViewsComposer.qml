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
            id: welcomeView
            button.onReleased: {
                stack.push(game)
                // gameView.gameItem.fieldWidth = settings.fieldWidth
                // gameView.gameItem.fieldHeight = settings.fieldHeight
            }
            // onActivated: {
            //     stack.push(game)
            // }
        }
    }

    Component {
        id: game
        GameView {
            id: gameView
            menuButton.onReleased: stack.pop()
        }
    }
}
