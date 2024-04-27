#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <iostream>
#include <string>

#include <kddockwidgets/Config.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/ViewFactory.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/views/MainWindow.h>

#include "Chip8Backend.hpp"
#include "Chip8Display.hpp"

class CustomViewFactory : public KDDockWidgets::QtQuick::ViewFactory
{
public:
    QUrl titleBarFilename() const override
    {
        return QUrl("qrc:/MyTitleBar.qml");
    }
    QUrl separatorFilename() const override
    {
        return QUrl("qrc:/MySeparator.qml");
    }
};

auto main(int argc, char* argv[]) -> int {
#ifdef Q_OS_WIN
  QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
  qmlRegisterType<Chip8Display>("my.b1te.cheapate", 1, 0, "Chip8Display");
  qmlRegisterType<Chip8Backend>("my.b1te.cheapate", 1, 0, "Chip8Backend");
  QGuiApplication app(argc, argv);
  KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

  auto& config = KDDockWidgets::Config::self();
  auto flags = config.flags() | KDDockWidgets::Config::Flag_TitleBarIsFocusable;

  config.setFlags(flags);
  config.setViewFactory(new CustomViewFactory());

  QQmlApplicationEngine appEngine;
  KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);
  appEngine.load((QUrl("qrc:/main.qml")));

  return QGuiApplication::exec();
}
