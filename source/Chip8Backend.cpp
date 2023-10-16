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
    auto cur_x = 0;
    auto cur_y = 0;
    while (!m_QuitThread) {
      if (cur_x == Chip8Display::WIDTH) {
        cur_x = 0;
        cur_y++;
      }
      int r = QRandomGenerator::global()->bounded(0, 255);
      int g = QRandomGenerator::global()->bounded(0, 255);
      int b = QRandomGenerator::global()->bounded(0, 255);
      m_Chip8Display->SetPixel(cur_x, cur_y,QColor::fromRgb(r,g,b));

      cur_x++;
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1000ms);
    }
  });
}
Chip8Backend::Chip8Backend(QObject* parent) : 
  QObject(parent),
  m_EmulatorThread(nullptr),
  m_QuitThread(false)
{

}
