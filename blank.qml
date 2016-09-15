import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import CSD.Percolation 1.0

Window {
    id: root
    objectName: "window"
    visible: true
    minimumWidth: 760
    minimumHeight: 470

    Percolation {
        id: perc
        objectName: "perc"
    }

    PercolationModel {
        id: model
        percolation: perc
    }

    PercolationView {
        id: view
        model: model
        gridSize: perc.gridSize
        anchors.fill: parent
        anchors.margins: 10
    }
}
