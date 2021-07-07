import QtQuick 2.0
import QtQuick.Controls 2.2
import SectionDraw 1.0

Item {
    id: waveViewrDetect
    width: 200
    height: 400
    //added for test temporary
    property variant myWaveArray: [40,0,55,55,55,0,10]
    property alias bdrawGrid: sectionDrawID.drawGrid
    property alias bdrawBGround: sectionDrawID.drawBGround
    property alias bdrawPierLine: sectionDrawID.drawPierLine
    property alias bdrawTravelLine: sectionDrawID.drawTravelLine
    property alias bdrawDegree: sectionDrawID.drawDegree
    property alias sectionDraw: sectionDrawID

    Rectangle{
        id: wave_area_rect
        width: parent.width
        height: parent.height
        property int wavebuffSize: myWaveArray.length

        SectionDraw{
            id: sectionDrawID
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            width: parent.width
            height: parent.height
            gridRowNum: 10
            gridColumnNum: 20
            borderWidth: width
            borderHeight: height
            updateTimer: 1000 //delay interval ms
            //lineColor: waveLinecolor

            drawGrid: true
            drawPierLine: true
            drawDegree: true
            drawBGround: true
            drawTest: false
            drawAreaBoder: true
            drawTravelLine: true

            onTooltip: {
                ToolTip.text = point;
                if (point != "") {
                    if (ToolTip.visible) {

                        ToolTip.visible = false;

                    }
                    else {
                        ToolTip.visible = true;

                    }
                    console.log("SectionDraw onTooltip!!!!!!!!!");

                }else {
                    ToolTip.visible = false;
                }

            }

            //xLineInterval: (borderWidth - 30*2)/177
            //waveMode: WaveViewer.SquareWave
            //lineHeight:  height*0.8
            //lineWidth: line_width
            //visible: encoderFrequencyGrant.isVisible
//            MouseArea {
//                id: mous
//                anchors.fill: parent
//                acceptedButtons: Qt.LeftButton
//                propagateComposedEvents: true

//                onClicked: {
//                    if (ToolTip.visible) {
//                        ToolTip.visible = false;
//                    }

//                    ToolTip.text = qsTr("Save the active project")
//                    if (ToolTip.visible) {

//                        ToolTip.visible = false;

//                    }
//                    else {
//                        ToolTip.visible = true;

//                    }



//                    console.log("SectionDraw MouseArea");
//                    console.log("mouseX:" +mous.mouseX + "\nmouseY:" + mous.mouseY)


////                    if (!mouseScaleButton.checked) {
////                        contextMenu.popup();
////                    }
////                    else
////                        mouse.accepted = false;

//                }
//            }
        }

        Rectangle {
            anchors.fill: sectionDrawID
            color: "transparent"
            border.color: "black"
            border.width: 2
        }


    }

//    Timer{
//        id: wave_update
//        interval: 500/10
//        repeat: true
//        running: sectionDrawID.visible
//        onTriggered:
//        {
//            sectionDrawID.xLineInterval = sectionDrawID.xLineInterval>sectionDrawID.lineWidth ? sectionDrawID.xLineInterval-sectionDrawID.lineWidth:0
//            for(var i = 0; i < wave_area_rect.wavebuffSize; ++i ){
//                sectionDrawID.newData = myWaveArray[i]
//            }
//            sectionDrawID.updateTimer = -1
//            running = false
//            //console.log("wave_update: wave_update is running .............",waveDiagnosticData.xLineInterval )
//        }
//    }

}


