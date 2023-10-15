#include <iostream>
#include <string>

#include <kddockwidgets/Config.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/ViewFactory.h>
#include <kddockwidgets/qtquick/views/MainWindow.h>


#include <QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Chip8Display.hpp"
#include "lib.hpp"

auto main(int argc, char* argv[]) -> int
{
  auto const lib = library {};
  auto const message = "Hello from " + lib.name + "!";
  std::cout << message << '\n';
  #ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
  qmlRegisterType<Chip8Display>("my.b1te.cheapate",1,0,"Chip8Display");
    QGuiApplication app(argc, argv);
    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

    auto &config = KDDockWidgets::Config::self();
    auto flags = config.flags() | KDDockWidgets::Config::Flag_TitleBarIsFocusable;

    config.setFlags(flags);

    QQmlApplicationEngine appEngine;
    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);
    appEngine.load((QUrl("qrc:/main.qml")));

  return app.exec();
}
