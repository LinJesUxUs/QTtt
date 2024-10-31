import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import linjesuxus.game
import linjesuxus.imageCell

Rectangle {
    id: root
    width: 300
    height: 480
    color: "black"

    GridView {
        model: Game
        delegate: delegate
        Component {
            id: delegate
            Image {
                id: img
                source: getImage
            }
        }
    }

    // Grid {
    //     anchors {
    //         horizontalCenter: root.horizontalCenter
    //         top: root.top
    //     }
    //     columns: 3
    //     Repeater {
    //         id: repeater
    //         model: 9
    //         Rectangle {
    //             id: cell
    //             width: root.width < root.height ? root.width / 3 : root.height / 3
    //             height: width
    //             Image {
    //                 id: img
    //                 anchors.fill: cell
    //                 source: game.getCell(index)
    //             }
    //             MouseArea {
    //                 anchors.fill: cell
    //                 onClicked: {
    //                     if (root.gameState === "run" && game.getBoard(
    //                                 index) === ' ') {
    //                         game.command(index)
    //                         img.source = game.getCell(index)
    //                         if (game.over() !== ' ') {
    //                             root.gameState = "over"
    //                             console.debug("Over setted")
    //                         }
    //                         console.debug(
    //                                     "Clicked " + index + " Over? " + game.over(
    //                                         ))
    //                     } else
    //                         console.debug(
    //                                     "NotClicked " + index + " Over? " + game.over(
    //                                         ))
    //                 }
    //             }
    //         }
    //     }
    // }
}
