#ifndef CHIP8DISPLAY_H
#define CHIP8DISPLAY_H

#include <QtQuick/QQuickPaintedItem>
class Chip8Display: public QQuickPaintedItem {
  Q_OBJECT
private:
public:
  Chip8Display(QQuickItem* parent=nullptr);

  void paint(QPainter* painter) override;


};

#endif
