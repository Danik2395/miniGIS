#include <QPainter>
#include <QPoint>
#include "gcanvas.h"
import gengine.types.render;

GCanvas::GCanvas(QWidget* parent) : QWidget(parent) {}

void GCanvas::draw()
{
    this->update();
    return;
}

void GCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::green, 5));

    QPoint point(50, 50);
    QPoint point1(150, 150);

    painter.drawLine(point, point1);
}
