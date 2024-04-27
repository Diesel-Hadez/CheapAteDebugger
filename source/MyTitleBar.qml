
import QtQuick 2.6
import "qrc:/kddockwidgets/qtquick/views/qml/" as KDDW

KDDW.TitleBar {
    id: root
    color:  sysPalette.window
    border.color: sysPalette.shadow
    SystemPalette {id: sysPalette}
    Text {
        id: title
        text: root.title
        color: sysPalette.text
        anchors {
            left: parent ? parent.left : undefined
            leftMargin: 5
            verticalCenter: parent.verticalCenter
        }
    }
}
