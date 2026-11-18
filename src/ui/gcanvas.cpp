#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPointF>
#include <QPolygonF>
#include <QPainterPath>
#include <algorithm>
#include <qbrush.h>
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
    void operator()(const geng::Polygon&)    const;
};




GCanvas::GCanvas(QWidget* parent) : QWidget(parent) {}

GCanvas::~GCanvas() = default;

void GCanvas::draw(std::vector<geng::RenderUnit>&& draw_sequence)
{
    this->draw_seq = std::move(draw_sequence);
    this->update();
    return;
}

void GCanvas::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    auto painter = QPainter(this);

    auto draw_unit = [&painter](const auto& unit) {
        std::visit(UnitDeductor{unit, painter}, unit.geometry);
    };

    std::ranges::for_each(draw_seq, draw_unit);
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

void set_style(QPainter& painter, const geng::Style& style)
{
    painter.setPen(QPen(to_QColor(style.main_color), style.thickness));
    painter.setBrush(QBrush(to_QColor(style.fill_color), Qt::SolidPattern));
}

void UnitDeductor::operator()(const geng::LineString& line) const
{
    namespace views  = std::views;
    namespace ranges = std::ranges;

    auto sublines = line.points | views::pairwise;

    auto draw_subline = [this](const auto& subline){
        auto [p1, p2] = subline;

        QPointF qp1(p1.x, p1.y);
        QPointF qp2(p2.x, p2.y);

        painter.drawLine(qp1, qp2);
    };

    set_style(painter, unit.style);

    ranges::for_each(sublines, draw_subline);
}

void UnitDeductor::operator()(const geng::Point& p) const
{
    QPointF qpoint(p.x, p.y);

    set_style(painter, unit.style);

    painter.drawPoint(qpoint);
}

void UnitDeductor::operator()(const geng::Polygon& poly) const
{
    // п.59
    namespace ranges = std::ranges;

    auto points_to_qpoly = [](QPolygonF& qpoly, const ranges::forward_range auto& point_sequence){
        ranges::for_each(point_sequence, [&qpoly](const auto& p){ qpoly << QPointF(p.x, p.y); });
    };

    QPolygonF qpoly_outer;

    points_to_qpoly(qpoly_outer, poly.outer);

    QPainterPath path;
    path.addPolygon(qpoly_outer);

    for (const auto& inner_points : poly.inner)
    {
        QPolygonF inner_qpoly;
        points_to_qpoly(inner_qpoly, inner_points);

        path.addPolygon(inner_qpoly);
    }

    set_style(painter, unit.style);

    painter.drawPath(path);
}
