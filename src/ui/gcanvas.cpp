#include <QPainter>
#include <QPoint>
#include <algorithm>
#include <qcolor.h>
#include <variant>
#include <ranges>
#include "gcanvas.h"
import gengine.types.render;
import gengine.types.primitives;

struct UnitDeductor
{
    const geng::RenderUnit& unit;
    QPainter& painter;

    void operator()(const geng::Point&)      const;
    void operator()(const geng::LineString&) const;
    void operator()(const geng::Segment&)    const;
    void operator()(const geng::Polygon&)    const;
};




GCanvas::GCanvas(QWidget* parent) : QWidget(parent) {}

GCanvas::~GCanvas() = default;

void GCanvas::draw(std::vector<geng::RenderUnit>&& draw_sequence)
{
    this->draw_sequence = std::move(draw_sequence);
    this->update();
    return;
}

void GCanvas::paintEvent(QPaintEvent *event)
{
    auto painter = QPainter(this);

    auto draw_unit = [this, &painter](const auto& unit) {
        std::visit(UnitDeductor{unit, painter}, unit.geometry);
    };

    std::ranges::for_each(draw_sequence, draw_unit);
}

QColor to_QColor(geng::Color color)
{
    return QColor(
            color.r,
            color.g,
            color.b,
            color.a
            );
}

void UnitDeductor::operator()(const geng::LineString& line) const
{
    namespace views  = std::views;
    namespace ranges = std::ranges;

    painter.setPen(QPen(to_QColor(unit.main_color), unit.thickness));

    auto sublines = line.points | views::pairwise;

    auto draw_subline = [this](const auto& subline){
        auto [p1, p2] = subline;

        QPoint qp1(p1.x, p1.y);
        QPoint qp2(p2.x, p2.y);

        painter.drawLine(qp1, qp2);
    };

    ranges::for_each(sublines, draw_subline);
}

void UnitDeductor::operator()(const geng::Point&) const
{
}

void UnitDeductor::operator()(const geng::Segment&) const
{
}

void UnitDeductor::operator()(const geng::Polygon&) const
{
}
