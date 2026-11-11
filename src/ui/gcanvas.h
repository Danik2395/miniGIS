#pragma once
#include <QWidget>
#include <QObject>
#include <QPainter>

class GCanvas : public QWidget
{
    Q_OBJECT

public:
    GCanvas(QWidget* parent = nullptr);

    void draw();

protected:
    void paintEvent(QPaintEvent *event) override;
};
