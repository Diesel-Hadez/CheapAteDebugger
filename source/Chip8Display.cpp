#include <cmath>
#include <utility>

#include "Chip8Display.hpp"

#include <qcolor.h>
#include <qpainter.h>

Chip8Display::Chip8Display(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_PenColor(QColor::fromRgb(255, 0, 0))
    , m_RefreshRate(this) {
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

void Chip8Display::paint(QPainter* painter) {
  m_RenderMutex.lock();
  QPen pen(QColorConstants::Black, 0);
  pen.setWidth(0);
  painter->setRenderHints(QPainter::Antialiasing, true);
  const double min_scale =
      std::min(static_cast<double>(boundingRect().width())
                   / static_cast<double>(Chip8Display::WIDTH),
               static_cast<double>(boundingRect().height())
                   / static_cast<double>(Chip8Display::HEIGHT));
  double integral = NAN;
  const double leftover = std::modf(min_scale, &integral);
  // Increase to add a border to
  // avoid artifacts in fractional scaling
  const double left_margin =
      std::floor((leftover * static_cast<double>(Chip8Display::WIDTH)) / 2.F);
  const double scale = std::floor(min_scale);
  for (int x = 0; x < Chip8Display::WIDTH; x++) {
    for (int y = 0; y < Chip8Display::HEIGHT; y++) {
      const double x_f = x;
      const double y_f = y;
      const auto& cur_pixel = m_ScreenPixels.at(x).at(y);
      pen.setColor(cur_pixel);
      painter->setPen(pen);
      const QRectF pixel_pos(
          left_margin + (x_f * scale), y_f * scale, scale, scale);
      painter->fillRect(pixel_pos, cur_pixel);
    }
  }
  m_RenderMutex.unlock();
}
