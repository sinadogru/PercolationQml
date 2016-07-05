import QtQuick 2.6
import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import CSD.Percolation 1.0

/* PercolationController is a UI for Percolation
*/
Item {
    property Percolation percolation

    RandomGridSiteGenerator {
        id: rng
        gridSize: percolation.gridSize
    }

    GridLayout {
        id: layout

        Button {
            text: qsTr("Open a Site")
            onClicked: percolation.open(rng.column, rng.row)
        }
        // TODO gridSize spinner
        // TODO percolation results
        // TODO simulate switch
    }
}
