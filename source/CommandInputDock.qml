import QtQuick 2.9
import QtQuick.Controls 2.15
import com.kdab.dockwidgets 2.0 as KDDW

Item {
  id: root
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
        color: "red"
        anchors.fill: parent
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
        background: Rectangle {
          color: "white"
          border.color: commandOutputView.enabled 
          ? "#21be2b" : "transparent"
        }
        placeholderText: "Command Outputs will be shown here"
        anchors {
          top: parent.top
          left: parent.left
          right: parent.right
          bottom: commandInputView.top
          margins: 5
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
          root.commandEntered(commandInputView.text);
          commandInputView.text = "";
        }
      }
      Component.onCompleted: {
       commandInputDock.isFocusedChanged.connect(root.isFocusedChanged); 
      }
    }
  }

  function addOutput(output) {
    commandOutputView.text += output + "\n";
  }
}
