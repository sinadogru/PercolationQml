import QtQuick 2.6
import CSD.Percolation 1.0

/* This view represents a NxN grid.
*/
Item {
    id: percolationView

    property PercolationModel model
    property int gridSize: 0


    GridView {
        id: view
        Rectangle {
            width: parent.width + border.width * 2
            height: parent.height + border.width * 2
            anchors.centerIn: parent
            border.width: 2
            z: -1
            border.color: "black"
        }
        anchors.centerIn: parent
        implicitWidth: __shorterSideSize
        implicitHeight: __shorterSideSize
        cellHeight: __cellSize
        cellWidth: __cellSize
        interactive: false
        model: percolationView.model

        delegate: Item {
            id: delegate
            width: percolationView.__cellSize
            height: percolationView.__cellSize
            Rectangle {
                anchors.fill: parent
                color: percolates?
                           view.delegateColorAnimation
                         : open ?
                               "blue"
                             : componentColor
            }
        }

        property color delegateColorAnimation
        SequentialAnimation on delegateColorAnimation {
            loops: Animation.Infinite
            ColorAnimation { from: "blue"; to: "#33FFFF"; duration: 2000 }
            ColorAnimation { from: "#33FFFF"; to: "blue"; duration: 2000 }
        }
    }

    property real __shorterSideSize: Math.min(width, height)
    property real __cellSize: __shorterSideSize / gridSize
}
