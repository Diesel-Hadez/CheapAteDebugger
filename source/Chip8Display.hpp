#ifndef CHIP8DISPLAY_H
#define CHIP8DISPLAY_H

#include <QtQuick/QQuickPaintedItem>
#include <mutex>
#include <qtimer.h>
class Chip8Display: public QQuickPaintedItem {
  Q_OBJECT
private:
  QColor m_PenColor;
  std::mutex m_RenderMutex;
public:
  QTimer m_RefreshRate;
  void SetPenColor(QColor color);
public:
  Chip8Display(QQuickItem* parent=nullptr);

  void paint(QPainter* painter) override;


};

#endif
