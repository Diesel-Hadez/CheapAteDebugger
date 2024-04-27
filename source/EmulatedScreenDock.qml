import QtQuick 2.9
import QtQuick.Controls 2.15
import com.kdab.dockwidgets 2.0 as KDDW
import my.b1te.cheapate 1.0

Item {
  property alias chip8Display:  __chip8Display
  id: root
  SystemPalette {id: sysPalette}
  KDDW.DockWidget {
    id: emulatedScreenDock
    uniqueName: "emulatedScreenDock"
    Item {
      anchors.fill: parent
      Rectangle {
        anchors.fill: parent
        color: sysPalette.window
      }
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
