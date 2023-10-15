#ifndef CHIP8_BACKEND_H
#define CHIP8_BACKEND_H
#include <QObject>
#include "Chip8Display.hpp"

class Chip8Backend : public QObject {
  Q_OBJECT
  Q_PROPERTY(Chip8Display* screenDisplay READ screenDisplay WRITE setScreenDisplay)
public:
  Chip8Display* screenDisplay() const {return m_Chip8Display;}
  void setScreenDisplay(Chip8Display *display) {m_Chip8Display = display;}


  Q_INVOKABLE void Run();
  Chip8Display* m_Chip8Display;
};

#endif
