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


    RowLayout {
        anchors.fill: parent
        PercolationView {
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 100
            model: model
            gridSize: root.gridSize
            cellWidth: 80
            cellHeight: 80
//            anchors.fill: parent
        }

        PercolationController {
            id: controller
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            percolation: perc
        }
    }
}
