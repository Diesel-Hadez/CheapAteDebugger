import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import com.kdab.dockwidgets 2.0 as KDDW

Item {
  id: root

  SystemPalette {id: sysPalette}
  // TO-DO: Maybe do parsing here instead,
  // then the arguments for this signal can be
  // something like 
  // commandEntered(Command command, Arguments args)
  signal commandEntered(string command)
  signal isFocusedChanged()
  KDDW.DockWidget {
    id: commandInputDock
    uniqueName: "commandInputDock"
    Item {
      visible: true
      anchors.fill: parent
      Rectangle {
        anchors.fill: parent
        color: sysPalette.window
      }
      ScrollView {
        id: commandOutputScrollView
        anchors {
          top: parent.top
          left: parent.left
          right: parent.right
          bottom: commandInputView.top
          margins: 5
        }
        TextArea {
          id: commandOutputView
          // On some platform (e.g: Mobile)
          // this might break some things, like how it's
          // supposed to be like inside a Flickable.
          // But here, it should be fine.
          selectByMouse: true
          font.family: "FiraCode Nerd Font"
          readOnly: true
          placeholderText: "Command Outputs will be shown here"
          }
      }
      TextField {
        id: commandInputView
        // On some platform (e.g: Mobile)
        // this might break some things, like how it's
        // supposed to be like inside a Flickable.
        // But here, it should be fine.
        selectByMouse: true
        font.family: "FiraCode Nerd Font"
        placeholderText: "Type Commands Here."
        anchors {
          bottom: parent.bottom
          left: parent.left
          right: parent.right
          margins: 5
        }

        onAccepted: {
          let command = commandInputView.text
          commandInputView.text = "";
          commandOutputView.text += ">> " + command + "\n";
          root.commandEntered(command);
        }
      }
      Component.onCompleted: {
       commandInputDock.isFocusedChanged.connect(root.isFocusedChanged); 
      }
    }
  }

  function addOutput(output) {
    commandOutputView.text += output + "\n";
    // Scroll to bottom
    commandOutputScrollView.ScrollBar.vertical.position = 1.0 - commandOutputScrollView.ScrollBar.vertical.size;
  }
}
