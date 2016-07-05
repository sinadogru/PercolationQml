import QtQuick 2.6

/* This view represents a NxN grid.
*/
GridView {
    id: view
//    width: 200
//    height: 200

    onModelChanged: d.n = model.rowCount();

    QtObject {
        id: d

        property int n: model.rowCount();
        onNChanged: console.log("n: " + n);

        property int shortSide: Math.min(view.width, view.height);
        onShortSideChanged: console.log("shortSide: " + shortSide);
        property int site: shortSide / n;
        onSiteChanged: console.log(site, view.width, view.height);
    }

    delegate: Rectangle {
        id: delegate
        width: d.site
        height: d.site
        color: open ?
                   "blue"
                 : index % 2 ?
                       "black"
                     : "white"
        border.width: 1
        border.color: "black"
        Component.onCompleted: console.log(width, height);
    }

//    property int n

//    property size size



//    QtObject {
//        id: d

//        property int shortSide: Math.min(size.width, size.height);
//        property int site: shortSide / n;
//    }

//    Repeater {
//        id: repeater
//        model: n * n

//        Rectangle {
//            id: delegate
//            width: d.site
//            height: d.site
//            color: index % 2 ? "black" : "white"
//            border.width: 1
//            border.color: "black"
//        }
//    }
}
