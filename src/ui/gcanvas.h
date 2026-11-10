#pragma once
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QPoint>

class GCanvas : public QWidget
{
    Q_OBJECT

public:
    GCanvas(QWidget* parent = nullptr) : QWidget(parent)
    {

    }

    void draw()
    {
        this->update();
        return;
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::green, 5));

        QPoint point(50, 50);
        QPoint point1(150, 150);

        painter.drawLine(point, point1);
    }
};
