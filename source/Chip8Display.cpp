#include "Chip8Display.hpp"
#include <qcolor.h>
#include <qpainter.h>

#include <cmath>
#include <utility>

Chip8Display::Chip8Display(QQuickItem* parent)
  : QQuickPaintedItem(parent),
    m_RefreshRate(this),
    m_PenColor(QColor::fromRgb(255,0,0)){
  using namespace std::chrono_literals;
  // Roughly 30 frames per second
  m_RefreshRate.setInterval(33ms);
  m_RefreshRate.start();
  for (int x = 0; x < Chip8Display::WIDTH; x++) {
    for (int y = 0; y < Chip8Display::HEIGHT; y++) {
      m_ScreenPixels.at(x).at(y) = QColorConstants::Black;
    }
  }
}

void Chip8Display::SetPixel(int x, int y, QColor color) {
  if (x < 0 || x >= Chip8Display::WIDTH) {
    return;
  }
  if (y < 0 || y >= Chip8Display::HEIGHT) {
    return;
  }
  auto xs = static_cast<size_t>(x);
  auto ys = static_cast<size_t>(y);
  m_RenderMutex.lock();
  m_ScreenPixels.at(xs).at(ys) = std::move(color);
  m_RenderMutex.unlock();
}

void Chip8Display::paint(QPainter* painter)  {
  m_RenderMutex.lock();
  QPen pen(QColorConstants::Black,0);
  pen.setWidth(0);
  painter->setRenderHints(QPainter::Antialiasing, true);
  const double scale= std::floor(std::min(
    (double)(boundingRect().width()) / (double)(Chip8Display::WIDTH),
    (double)(boundingRect().height()) / (double) (Chip8Display::HEIGHT)));
  for (int x = 0; x < Chip8Display::WIDTH; x++) {
    for (int y = 0; y < Chip8Display::HEIGHT; y++) {
      const double x_f = x;
      const double y_f = y;
      const auto& cur_pixel = m_ScreenPixels.at(x).at(y);
      pen.setColor(cur_pixel);
      painter->setPen(pen);
      const QRectF pixel_pos(x_f*scale, y_f*scale, scale, scale);
      painter->fillRect(pixel_pos, cur_pixel);
    }
  }
  m_RenderMutex.unlock();
}
