import QtQuick 2.6
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
  visible: true
  width: 1000
  height: 800

  KDDW.LayoutSaver {
      id: layoutSaver
  }

  menuBar: MenuBar {
    Menu {
      title: qsTr("&File")

      Action {
        text: qsTr("Save layout")
        onTriggered: {
          layoutSaver.saveToFile("mySavedLayout.json");
        }
      }
      Action {
        text: qsTr("Restore layout")
        onTriggered: {
          layoutSaver.restoreFromFile("mySavedLayout.json");
        }
      }
    }

    Menu {
      title: qsTr("&Debug")
      Action {
        text: qsTr("Run")
      }
      Action {
        text: qsTr("Step")
      }
      Action {
        text: qsTr("Break")
      }
    }
  }

  header: ToolBar {
    RowLayout {
      anchors {
        left: parent.left
        top: parent.top
        bottom: parent.bottom
      } 
      ToolButton {
        text: qsTr("⏵")
      }
      ToolButton {
        text: qsTr("⏸")
      }
      ToolButton {
        text: qsTr("⏹")
      }
    }
  }

  KDDW.DockingArea {
      id: dockWidgetArea
      anchors.fill: parent
      uniqueName: "MyMainLayout"

      KDDW.DockWidget {
        id: disassemblyDock
        uniqueName: "disassemblyDock"
        source: "qrc:/DisassemblyDock.qml"
        onIsFocusedChanged: {
          console.log("Focus changed to DisassemblyDock!");
        }
      }
      CommandInputDock {
        id: commandInputDock
        onCommandEntered: (command) => {
          console.log(`Entered Command ${command}!`);
          if (command === "/about") {
            commandInputDock.addOutput(""+
            "-----------CheapAteDebugger-----------\n"+
            "A Chip8 Emulator/Debugger developed by\n"+
            "           Diesel-Hadez               \n");
          }
        }
        onIsFocusedChanged: {
          console.log("Focus changed to CommandInputDock!");
        }
      }
      KDDW.DockWidget {
        id: emulatedScreenDock
        uniqueName: "emulatedScreenDock"
        source: "qrc:/EmulatedScreenDock.qml"
        onIsFocusedChanged: {
          console.log("Focus changed to EmulatedScreenDock!");
        }
      }
      Component.onCompleted: {
          console.log("Starting CheapAteDebugger...");
          addDockWidget(disassemblyDock, KDDW.KDDockWidgets.Location_OnLeft)
          addDockWidget(emulatedScreenDock, KDDW.KDDockWidgets.Location_OnRight)
          addDockWidget(commandInputDock, KDDW.KDDockWidgets.Location_OnBottom)
          layoutSaver.restoreFromFile("mySavedLayout.json");
      }
    }
}
