#ifndef CHIP8DISPLAY_H
#define CHIP8DISPLAY_H

#include <array>
#include <mutex>

#include <qtimer.h>

#include <QtQuick/QQuickPaintedItem>
class Chip8Display : public QQuickPaintedItem {
  Q_OBJECT
public:
  constexpr static int WIDTH = 64;
  constexpr static int HEIGHT = 32;

private:
  QColor m_PenColor;
  std::mutex m_RenderMutex;
  using Chip8Screen = std::array<std::array<QColor, HEIGHT>, WIDTH>;
  Chip8Screen m_ScreenPixels;

public:
  QTimer m_RefreshRate;

  explicit Chip8Display(QQuickItem* parent = nullptr);

  void paint(QPainter* painter) override;
  void SetPixel(int x, int y, QColor color);
};

#endif
