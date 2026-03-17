// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.
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
