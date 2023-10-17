#ifndef CHIP8DISPLAY_H
#define CHIP8DISPLAY_H

#include <QtQuick/QQuickPaintedItem>
#include <mutex>
#include <qtimer.h>
#include <array>
class Chip8Display: public QQuickPaintedItem {
  Q_OBJECT
public:
  constexpr static int WIDTH=64;
  constexpr static int HEIGHT=32;
private:
  QColor m_PenColor;
  std::mutex m_RenderMutex;
  using Chip8Screen=std::array<
    std::array<QColor, HEIGHT>,
    WIDTH>;
  Chip8Screen m_ScreenPixels;
public:
  QTimer m_RefreshRate;
public:
  Chip8Display(QQuickItem* parent=nullptr);

  void paint(QPainter* painter) override;
  void SetPixel(int x, int y, QColor color);


};

#endif
