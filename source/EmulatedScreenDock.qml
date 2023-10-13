import QtQuick 2.9
import QtQuick.Controls 2.15
import com.kdab.dockwidgets 2.0 as KDDW

Item {
  id: root
  KDDW.DockWidget {
    id: emulatedScreenDock
    uniqueName: "emulatedScreenDock"
    Item {
      anchors.fill: parent
      Rectangle {
        color: "red"
        anchors {
          left: parent.left
          right: parent.right
          verticalCenter: parent.verticalCenter
        }
        height: width / 2
      }
    }
  }
}
