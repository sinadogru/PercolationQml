import QtQuick 2.6
import QtQuick.Window 2.2
import CSD.Percolation 1.0

Window {
    visible: true
    width: 300
    height: 200

    GridView {
        cellWidth: 80; cellHeight: 80
        implicitWidth: cellWidth * 3
        implicitHeight: cellHeight * 3
        model: ["1", "2", "3", "1", "2", "3", "1", "2", "3",]
        interactive: false
        delegate: Item {
            width: 80
            height: 80
            Column {
                anchors.fill: parent
                Rectangle {
                    color: "red"
                    border.color: "black"
//                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    Text {
                        anchors.centerIn: parent
                        text: modelData
                    }
                }
            }
        }
    }

//    Percolation {
//        id: perc
//        gridSize: 5
//    }

//    PercolationModel {
//        id: model
//        percolation: perc
//    }

//    PercolationView {
//        id: view
//        anchors.fill: parent
//        model: model
//    }

//    PercolationController {
//        id: controller
//        percolation: perc
//    }
}
