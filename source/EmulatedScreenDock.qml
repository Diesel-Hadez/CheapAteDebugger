import QtQuick 2.9
import QtQuick.Controls 2.15
import com.kdab.dockwidgets 2.0 as KDDW
import my.b1te.cheapate 1.0

Item {
  property alias chip8Display:  __chip8Display
  id: root
  KDDW.DockWidget {
    id: emulatedScreenDock
    uniqueName: "emulatedScreenDock"
    Item {
      anchors.fill: parent
      Chip8Display {
        id: __chip8Display
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
