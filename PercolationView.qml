import QtQuick 2.6
import CSD.Percolation 1.0

/* This view represents a NxN grid.
*/
Item {
    id: percolationView

    property alias cellWidth: view.cellWidth
    property alias cellHeight: view.cellHeight
    property PercolationModel model
    property int gridSize: 0

    // TODO encapsulate cellWidth and cellHeight. PercolationView can implicitly change cellHeight and cellWidth according to physical size and gridSize.

    GridView {
        id: view
        anchors.centerIn: parent
        implicitWidth: cellWidth * gridSize
        implicitHeight: cellHeight * gridSize
        interactive: false
        model: percolationView.model

        delegate: Item {
            id: delegate
            width: cellWidth
            height: cellHeight
            Rectangle {
                anchors.fill: parent
                color: percolates?
                           view.delegateColorAnimation
                         : open ?
                               "blue"
                             : index % 2 ?
                                   "black"
                                 : "white"
                border.width: 1
                border.color: "black"
            }
        }

        property color delegateColorAnimation
        SequentialAnimation on delegateColorAnimation {
            loops: Animation.Infinite
            ColorAnimation { from: "blue"; to: "#33FFFF"; duration: 2000 }
            ColorAnimation { from: "#33FFFF"; to: "blue"; duration: 2000 }
        }
    }
}
