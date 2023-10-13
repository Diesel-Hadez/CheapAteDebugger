import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
  id: root
  // For demonstration purpose.
  // Will move elsewhere later.
  property int program_counter: 0
  Binding {
    target: disassemblyDock
    property: "program_counter"
    value: root.program_counter
  }

  width: 1000
  height: 800

  KDDW.LayoutSaver {
      id: layoutSaver
  }

  Shortcut {
    // TO-DO: Differentiate Step Into and Step Over
    sequences: ["F10", "F11"]
    onActivated: {
      root.step_forward();
    }
  }
  Shortcut {
    sequences: ["Shift+F10", "Shift+F11"]
    onActivated: {
      root.step_backward();
    }
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
        onTriggered: {
         root.step_forward();
        }
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
      ToolButton {
        text: qsTr("⏩")
        onClicked: {
          root.step_forward();
        }
      }
      ToolButton {
        text: qsTr("⏪")
        onClicked: {
          root.step_backward();
        }
      }
    }
  }

  KDDW.DockingArea {
      id: dockWidgetArea
      anchors.fill: parent
      uniqueName: "MyMainLayout"

      DisassemblyDock {
        id: disassemblyDock
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
          else {
            commandInputDock.addOutput(""+
            "Command \"" + command + "\" not found!\n")
          }
        }
        onIsFocusedChanged: {
          console.log("Focus changed to CommandInputDock!");
        }
      }
      EmulatedScreenDock {
        id: emulatedScreenDock
      }
      Component.onCompleted: {
          console.log("Starting CheapAteDebugger...");
          addDockWidget(disassemblyDock, KDDW.KDDockWidgets.Location_OnLeft)
          addDockWidget(emulatedScreenDock, KDDW.KDDockWidgets.Location_OnRight)
          addDockWidget(commandInputDock, KDDW.KDDockWidgets.Location_OnBottom)
          layoutSaver.restoreFromFile("mySavedLayout.json");
      }
    }

    function step_forward() {
      root.program_counter += 1;
    }
    function step_backward() {
      root.program_counter -= root.program_counter > 0 ? 1 : 0;
    }
}
