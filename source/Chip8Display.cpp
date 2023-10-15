#include "Chip8Display.hpp"
#include <qpainter.h>

Chip8Display::Chip8Display(QQuickItem* parent)
  : QQuickPaintedItem(parent) {

}

void Chip8Display::paint(QPainter* painter)  {
  QPen pen(QColor::fromRgb(255,0,0), 2);

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);
  painter->drawPie(boundingRect().adjusted(1,1,-1,-1), 90 * 16, 290 * 16);

}
