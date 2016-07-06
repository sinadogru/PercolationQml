import QtQuick 2.6
import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import CSD.Percolation 1.0

/* PercolationController is a UI for Percolation
*/
Item {
    id: percolationController
    property Percolation percolation
    property int gridSize: 5

    RandomComponentGenerator {
        id: rng
        gridSize: percolation.gridSize
    }

    PercolationStats {
        id: stats
    }

    Connections {
        target: percolation
        onSiteOpened: ++__openComponentCounter;
        onPercolated: stats.percolated(__openComponentCounter, __totalComponent);
    }

    ColumnLayout {
        id: layout
        anchors.centerIn: parent
        spacing: 15

        Button {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            text: qsTr("Open a Component")
            enabled: !percolation.isPercolates
            onClicked: {
                var i;
                var j;
                do {
                    i = rng.column;
                    j = rng.row;
                } while (percolation.isComponentOpen(i, j));
                percolation.openComponent(i, j);
//                percolation.openComponent(rng.column, rng.row);
            }
        }
        GroupBox {
            Layout.alignment: Qt.AlignCenter
//            Layout.fillWidth: true
            title: qsTr("Percolation")
            GridLayout {
                anchors.fill: parent
                columns: 2
                // TODO refactor label text
                Label { text: qsTr("Opened"); Layout.alignment: Qt.AlignRight }
                Frame {
                    Layout.alignment: Qt.AlignCenter
                    Label { text: __openComponentCounter + "/" + __totalComponent }
                }
                Label { text: qsTr("Grid Size") }
                SpinBox {
                    enabled: !__openComponentCounter && !percolation.isPercolates
                    value: percolationController.gridSize
                    onValueChanged: percolationController.gridSize = value;
                }
                Button {
                    Layout.columnSpan: 2
                    Layout.alignment: Qt.AlignCenter
                    enabled: percolation.isPercolates
                    text: qsTr("Reset Percolation")
                    onClicked: {
                        percolation.resetPercolation();
                        __openComponentCounter = 0;
                    }
                }
            }
        }

        GroupBox {
            Layout.alignment: Qt.AlignCenter
//            Layout.fillWidth: true
            title: qsTr("Percolation Stats")
            GridLayout {
                anchors.fill: parent
                columns: 2
                Label { text: qsTr("Mean:"); Layout.alignment: Qt.AlignCenter }
                Frame {
                    Layout.alignment: Qt.AlignCenter
                    Label { text: stats.mean }
                }
                Label { text: qsTr("Std Dev:"); Layout.alignment: Qt.AlignCenter }
                Frame {
                    Layout.alignment: Qt.AlignCenter
                    Label { text: stats.stddev }
                }
                Button {
                    Layout.columnSpan: 2
                    Layout.alignment: Qt.AlignCenter
                    text: qsTr("Reset Stats")
                    onClicked: stats.resetStats();
                }
                // TODO percolation count
            }
        }
        // TODO simulate switch
    }


    property int __openComponentCounter: 0
    property int __totalComponent: gridSize * gridSize
}
