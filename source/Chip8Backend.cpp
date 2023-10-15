#include "Chip8Backend.hpp"
#include <qnamespace.h>
#include "Chip8Display.hpp"
#include <chrono>
#include <QRandomGenerator>

void Chip8Backend::Run() {
  if (m_EmulatorThread != nullptr) {return;}
  qDebug() << "Running Chip8 Backend!\n";
  QObject::connect(&(m_Chip8Display->m_RefreshRate), &QTimer::timeout,
                   this, [&disp = this->m_Chip8Display](){disp->update();},
                   Qt::DirectConnection);
  m_EmulatorThread = std::make_unique<std::thread>([&](){
    while (true) {
      int r = QRandomGenerator::global()->bounded(0, 255);
      int g = QRandomGenerator::global()->bounded(0, 255);
      int b = QRandomGenerator::global()->bounded(0, 255);
      m_Chip8Display->SetPenColor(QColor::fromRgb(r,g,b));
      qDebug() << "Set Pen Color\n";
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1000ms);
    }
  });
}
Chip8Backend::Chip8Backend(QObject* parent) : 
  QObject(parent),
  m_EmulatorThread(nullptr)
{

}
