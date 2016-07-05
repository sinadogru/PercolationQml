import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import CSD.Percolation 1.0

Window {
    id: root
    visible: true
    width: 700
    height: 500

    property int gridSize: 5

    Percolation {
        id: perc
        gridSize: root.gridSize
    }

    PercolationModel {
        id: model
        percolation: perc
    }


    PercolationView {
        id: view
        model: model
        gridSize: root.gridSize
        cellWidth: 80
        cellHeight: 80
        anchors.fill: parent
    }

    PercolationController {
        id: controller
        percolation: perc
    }
}
