import QtQuick 2.6
import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import CSD.Percolation 1.0

/* PercolationController is a UI for Percolation
*/
Item {
    property Percolation percolation

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
        Frame {
            Layout.alignment: Qt.AlignCenter
            Label { text: __openComponentCounter + "/" + __totalComponent }
        }
        GroupBox {
            Layout.alignment: Qt.AlignCenter
            title: qsTr("Percolation Stats")
            GridLayout {
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
            }
        }

        // TODO gridSize spinner
        // TODO percolation stats
        // TODO simulate switch
    }

    property int __gridSize: percolation.gridSize
    property int __openComponentCounter: 0
    property int __totalComponent: __gridSize * __gridSize
}
