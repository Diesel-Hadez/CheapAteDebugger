import QtQuick 2.9
import QtQuick.Controls 2.15

Item {
  anchors.fill: parent
  Rectangle {
    color: "red"
    anchors.fill: parent
  }
  TextField {
    placeholderText: "TextField to test focus"
    anchors {
      bottom: parent.bottom
      left: parent.left
      right: parent.right
      margins: 5
    }
  }
}
