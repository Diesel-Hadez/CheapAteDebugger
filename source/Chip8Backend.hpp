#ifndef CHIP8_BACKEND_H
#define CHIP8_BACKEND_H
#include <QObject>
#include <memory>
#include <thread>

using ThreadPtr = std::unique_ptr<std::thread>;

class Chip8Display;
class Chip8Backend : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      Chip8Display* screenDisplay READ screenDisplay WRITE setScreenDisplay)
private:
  ThreadPtr m_EmulatorThread;
  bool m_QuitThread;

public:
  explicit Chip8Backend(QObject* parent = nullptr);
  ~Chip8Backend() override {
    if (m_EmulatorThread) {
      m_QuitThread = true;
      m_EmulatorThread->join();
    }
  }
  // NOLINTBEGIN
  auto screenDisplay() const -> Chip8Display* { return m_Chip8Display; }
  void setScreenDisplay(Chip8Display* display) { m_Chip8Display = display; }
  // NOLINTEND

  Q_INVOKABLE void Run();

  // NOLINTNEXTLINE
  Chip8Display* m_Chip8Display;
};

#endif
