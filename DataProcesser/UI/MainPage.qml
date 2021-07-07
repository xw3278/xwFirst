import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//import SectionDraw 1.0
/*SectionDraw {
    id: sectionDraw
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.rightMargin: 20
    anchors.topMargin: 20
    anchors.leftMargin: 20

    width: 200
    height: 400

}*/

Item {
    id: mainPage

    Text {
        id: titleID
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        text: modifyTitleID.text
        color: "red"
        font.bold: true
        visible: true
    }

    Loader {
        id: loadWaveViewerID
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 20
        anchors.topMargin: 20
        anchors.leftMargin: 20
        source: "WaveViewer.qml"

        Connections {
            target: loadWaveViewerID.item
        }
    }

    Row {
        id: inputRow
        spacing: 10
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: loadWaveViewerID.bottom
        anchors.topMargin: 40

        Text {
            text: qsTr("输入名字：")
            font.pointSize: 15
            font.family: "Helvetica"
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {
            width: 100
            height: 24
            color: "lightgrey"
            border.color: "grey"

            TextInput {
                id:modifyTitleID
                anchors.fill: parent
                anchors.margins: 2
                font.pointSize: 15
                focus: true
                clip: true
                onAccepted: console.log("accepted")
            }
        }
    }

    Row {
        id: controlRow
        spacing: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: inputRow.bottom
        anchors.topMargin: 40

        CheckBox {
            id:drawGridCheck
            text: qsTr("draw grid")
            checked: true
            style: CheckBoxStyle {
                label: Label{
                    text:drawGridCheck.text
                    font.pixelSize: 15
                }
            }
            onCheckedChanged: {
               if(drawGridCheck.checked === false) {
                   console.log("Now is false")
                   loadWaveViewerID.item.bdrawGrid = false
               }else {
                   loadWaveViewerID.item.bdrawGrid = true
                   console.log("Now is true")
               }
            }
        }

        CheckBox {
            id:drawBackground
            text: qsTr("draw background")
            checked: true
            style: CheckBoxStyle {
                label: Label{
                    text:drawBackground.text
                    font.pixelSize: 15
                }
            }
            onCheckedChanged: {
               if(drawBackground.checked === false) {
                   loadWaveViewerID.item.bdrawBGround = false
               }else {
                   loadWaveViewerID.item.bdrawBGround = true
               }
            }

        }

        CheckBox {
            id:drawPier
            text: qsTr("draw pier")
            checked: true
            style: CheckBoxStyle {
                label: Label{
                    text:drawPier.text
                    font.pixelSize: 15
                }
            }
            onCheckedChanged: {
               if(drawPier.checked === false) {
                   loadWaveViewerID.item.bdrawPierLine = false
               }else {
                   loadWaveViewerID.item.bdrawPierLine = true
               }
            }
        }

        CheckBox {
            id:drawLine
            text: qsTr("draw line")
            checked: true
            style: CheckBoxStyle {
                label: Label{
                    text:drawLine.text
                    font.pixelSize: 15
                }
            }
            onCheckedChanged: {
               if(drawLine.checked === false) {
                   loadWaveViewerID.item.bdrawTravelLine = false
               }else {
                   loadWaveViewerID.item.bdrawTravelLine = true
               }
            }
        }

        CheckBox {
            id:drawDegree
            text: qsTr("draw degree")
            checked: true
            style: CheckBoxStyle {
                label: Label{
                    text:drawDegree.text
                    font.pixelSize: 15
                }
            }
            onCheckedChanged: {
               if(drawDegree.checked === false) {
                   loadWaveViewerID.item.bdrawDegree = false
               }else {
                   loadWaveViewerID.item.bdrawDegree = true
               }
            }
        }


    }


    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        text: "Screen Shot"
        onClicked: {
            loadWaveViewerID.item.sectionDraw.screenShot()
        }

    }
}
