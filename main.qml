import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls 1.4
import Qt.labs.platform 1.1 as Lab
import QtQuick.Controls 2.15
import Test 1.0
ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    HttpRequest {
        id:httpReq
    }

    Dialog {
        title: "Test Http"
        //modality: true ? Qt.WindowModal : Qt.NonModal
        id:testw
        x: (window.width - width) / 2
        y: (window.height - height) / 2
        visible: false
        Row {
            width: window.width
            spacing: 5
            Button{
                text:"Get"
                onClicked: httpReq.get("https://en.cppreference.com/w/cpp/memory/unique_ptr")
            }
            Button{
                text:"Post"
            }
            Button {
                text: "Hide"
                onClicked: testw.visible = false
            }
        }
        onAccepted: {
        }
        onRejected: {}
    }

    Column {
        id:root
        width: parent.width
        height: parent.height
        padding: 5
        spacing: 5
        Row {
            visible: true
            width: window.width
            spacing: 5
            Button{
                text:"Show"
                onClicked: testw.visible = true
            }
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
        TextField {
            width: parent.width - parent.spacing*2
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: -window.height
        width: window.width
        //window is id of the ApplicationWindow
        function calcY(){
          if(!window.activeFocusItem){
            return -window.height
          }          
          var mouseAreaGlobalPosition = root.mapToGlobal(window.activeFocusItem.x, window.activeFocusItem.y)
          console.log(window.y,mouseAreaGlobalPosition.y,mouseAreaGlobalPosition.y-window.y)
          var ypos = mouseAreaGlobalPosition.y-window.y+window.activeFocusItem.height
          console.log("activeFocusItem.y",window.activeFocusItem.y,"activeFocusItem.height",window.activeFocusItem.height,"ypos",ypos,"window.height",window.height,"window.y",window.y,"inputPanel.height",inputPanel.height);
          if(ypos+inputPanel.height> window.height) {
            ypos -= (window.activeFocusItem.height+inputPanel.height)
          }
          return ypos
        }
        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: inputPanel.calcY();
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
