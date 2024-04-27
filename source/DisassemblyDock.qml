import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.kdab.dockwidgets 2.0 as KDDW


Item {
  id: root
  signal isFocusedChanged()
  property alias program_counter: disassemblyLv.currentIndex
  SystemPalette {id: sysPalette}

  ListModel {
    id: mockDisassemblyCode
    ListElement { address: 0; code: "XOR V0, V0" }
    ListElement { address: 1; code: "XOR V1, V1" }
    ListElement { address: 2; code: "CALL 0x123" }
    ListElement { address: 3; code: "JP V0, 0x05b" }
    ListElement { address: 4; code: "LD V2, 0x001" }
    ListElement { address: 5; code: "XOR V0, V0" }
    ListElement { address: 6; code: "XOR V1, V1" }
    ListElement { address: 7; code: "CALL 0x123" }
    ListElement { address: 8; code: "JP V0, 0x05b" }
    ListElement { address: 9; code: "LD V2, 0x001" }
    ListElement { address: 10; code: "XOR V0, V0" }
    ListElement { address: 11; code: "XOR V1, V1" }
    ListElement { address: 12; code: "CALL 0x123" }
    ListElement { address: 13; code: "JP V0, 0x05b" }
    ListElement { address: 14; code: "LD V2, 0x001" }
    ListElement { address: 15; code: "LD V2, 0x001" }
    ListElement { address: 16; code: "XOR V1, V1" }
    ListElement { address: 17; code: "CALL 0x123" }
    ListElement { address: 18; code: "JP V0, 0x05b" }
    ListElement { address: 19; code: "LD V2, 0x001" }
    ListElement { address: 20; code: "XOR V0, V0" }
    ListElement { address: 21; code: "XOR V1, V1" }
    ListElement { address: 22; code: "CALL 0x123" }
    ListElement { address: 23; code: "JP V0, 0x05b" }
    ListElement { address: 24; code: "LD V2, 0x001" }
  }

  Component {
    id: assemblyLineDelegate
    RowLayout {
      id: rl
      Text {
        text: "0x" + address.toString(16).toUpperCase()
        color: sysPalette.text
        font.pixelSize: 12
      }
      Text {
        text: code
        color: sysPalette.text
        font.pixelSize: 18
      }
    }
  }

  KDDW.DockWidget {
    id: disassemblyDock
    uniqueName: "disassemblyDock"
    Item {
      id: disassemblyItem
      anchors.fill: parent
      Rectangle {
        anchors.fill: parent
        color: sysPalette.window
      }
      ListView {
        id: disassemblyLv
        clip: true
        anchors.fill: parent
        anchors.margins: 5
        model: mockDisassemblyCode
        preferredHighlightBegin: currentItem.height * 2
        preferredHighlightEnd: parent.height - 
            (currentItem.height * 2) - 
            anchors.margins
        highlightRangeMode: ListView.ApplyRange
        highlight: Rectangle {
          anchors {
            left: parent.left
            right: parent.right
          }
          color: sysPalette.highlight
        }
        delegate: assemblyLineDelegate
      }
    }
    Component.onCompleted: {
     disassemblyDock.isFocusedChanged.connect(root.isFocusedChanged); 
    }
  }
}
