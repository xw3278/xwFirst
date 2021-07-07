import QtQuick 2.0

Rectangle {
    width: 800
    height: 400
    color: "darkCyan"

    Loader {
        id: mainPageID
        anchors.fill: parent
        source: "MainPage.qml"

        Connections {
            target: mainPageID.item
        }
    }

}
