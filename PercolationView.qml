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

    // TODO encapsulate cellWidth and cellHeight. PercolationView can implicitly change cellHeight and cellWidth
    // according to physical size and gridSize.

    GridView {
        id: view
        anchors.centerIn: parent
        implicitWidth: cellWidth * gridSize
        implicitHeight: cellHeight * gridSize
        interactive: false
        model: percolationView.model

        delegate: Rectangle {
            id: delegate
            width: cellWidth
            height: cellHeight
            color: open ?
                       "blue"
                     : index % 2 ?
                           "black"
                         : "white"
            border.width: 1
            border.color: "black"
        }
    }
}
