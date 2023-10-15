#ifndef CHIP8_BACKEND_H
#define CHIP8_BACKEND_H
#include <QObject>
#include <memory>
#include <thread>

using ThreadPtr = std::unique_ptr<std::thread>;

class Chip8Display;
class Chip8Backend : public QObject {
  Q_OBJECT
  Q_PROPERTY(Chip8Display* screenDisplay READ screenDisplay WRITE setScreenDisplay)
private:
  ThreadPtr m_EmulatorThread;
public:
  Chip8Backend(QObject* parent=nullptr);
  ~Chip8Backend() {
    if (m_EmulatorThread) {
      m_EmulatorThread->join();
    }
  }
  Chip8Display* screenDisplay() const {return m_Chip8Display;}
  void setScreenDisplay(Chip8Display *display) {m_Chip8Display = display;}


  Q_INVOKABLE void Run();
  Chip8Display* m_Chip8Display;
};

#endif
