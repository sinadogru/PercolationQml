import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import CSD.Percolation 1.0

Window {
    id: root
    visible: true
    minimumWidth: 760
    minimumHeight: 470

    Percolation {
        id: perc
        gridSize: controller.gridSize
    }

    PercolationModel {
        id: model
        percolation: perc
    }


    RowLayout {
        anchors.fill: parent
        PercolationView {
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 30
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 100
            model: model
            gridSize: controller.gridSize
        }

        PercolationController {
            id: controller
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 30
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
            Layout.alignment: Qt.AlignCenter
            percolation: perc

        }
    }
}
