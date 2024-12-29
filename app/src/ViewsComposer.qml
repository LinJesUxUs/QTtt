import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    width: 300
    height: 480
    visible: true
    Material.theme: Material.Dark
    Material.accent: Material.color(Material.BlueGrey, Material.Shade200)
    Material.background: Material.Gray
    Material.foreground: Material.color(Material.LightBlue, Material.Shade50)
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
