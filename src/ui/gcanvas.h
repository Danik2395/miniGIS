#pragma once
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <vector>

namespace geng
{
struct RenderUnit;
} // namespace

class GCanvas : public QWidget
{
    Q_OBJECT

private:
    std::vector<geng::RenderUnit> draw_sequence;

public:
    GCanvas(QWidget* parent = nullptr);

    ~GCanvas() override;

    void draw(std::vector<geng::RenderUnit>&& draw_sequence);

protected:
    void paintEvent(QPaintEvent *event) override;
};
