#include "Chip8Display.hpp"
#include <qpainter.h>

Chip8Display::Chip8Display(QQuickItem* parent)
  : QQuickPaintedItem(parent),
    m_RefreshRate(this),
    m_PenColor(QColor::fromRgb(255,0,0)){
  using namespace std::chrono_literals;
  m_RefreshRate.setInterval(1000ms);
  m_RefreshRate.start();
}
void Chip8Display::SetPenColor(QColor color){
    m_RenderMutex.lock();
    m_PenColor = color;
    m_RenderMutex.unlock();
  }


void Chip8Display::paint(QPainter* painter)  {
  m_RenderMutex.lock();
  QPen pen(m_PenColor,2);
  m_RenderMutex.unlock();

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);
  painter->drawPie(boundingRect().adjusted(1,1,-1,-1), 90 * 16, 290 * 16);

}
