#include "blockparts.h"

#include <QMouseEvent>
#include <QPainter>
#include "qnamespace.h"

BlockParts::BlockParts(BlockParts::Decoration top, BlockParts::Decoration bottom, QWidget *parent)
    : QWidget(parent)
    , top(top)
    , bottom(bottom)
    , layout(QBoxLayout::LeftToRight, this)
    , label("Hola!")
{
    layout.addWidget(&label);
    layout.addWidget(&input);

    setContentsMargins(BORDER_THICKNESS, BORDER_THICKNESS, BORDER_THICKNESS, NOTCH_HEIGHT + BORDER_THICKNESS);
    adjustSize();

    updateShape();

    setAttribute(Qt::WA_TranslucentBackground);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setToolTip(tr("Bloque!"));
}

void BlockParts::resizeEvent(QResizeEvent*) {
    updateShape();
}

void BlockParts::updateShape() {
    qDebug() << "shape updated!";
    static const int slopeW = NOTCH_HEIGHT * NOTCH_INV_SLOPE;
    static const QPoint slopePoints[] = {
        QPoint(NOTCH_LEFT_GAP, 0),
        QPoint(NOTCH_LEFT_GAP + slopeW, NOTCH_HEIGHT),
        QPoint(NOTCH_LEFT_GAP + NOTCH_WIDTH - slopeW, NOTCH_HEIGHT),
        QPoint(NOTCH_LEFT_GAP + NOTCH_WIDTH, 0),
    };

    const auto rect = this->contentsRect();
    const QPoint offsetTopLeft = (top == BlockParts::Offset
                                    ? rect.topLeft() + QPoint(NOTCH_LEFT_GAP * 2, 0)
                                    : rect.topLeft());
    const QPoint offsetBottomLeft = (bottom == BlockParts::Offset
                                        ? rect.bottomLeft() + QPoint(NOTCH_LEFT_GAP * 2, 0)
                                        : rect.bottomLeft());

    shape = {
        rect.bottomLeft(),
        rect.topLeft(),
        offsetTopLeft,
    };

    if (top != BlockParts::Flat)
        shape.insert(shape.end(), {
            offsetTopLeft + slopePoints[0],
            offsetTopLeft + slopePoints[1],
            offsetTopLeft + slopePoints[2],
            offsetTopLeft + slopePoints[3],
        });

    shape.insert(shape.end(), {
        rect.topRight(),
        rect.bottomRight(),
    });

    if (bottom != BlockParts::Flat)
        shape.insert(shape.end(), {
            offsetBottomLeft + slopePoints[3],
            offsetBottomLeft + slopePoints[2],
            offsetBottomLeft + slopePoints[1],
            offsetBottomLeft + slopePoints[0],
            offsetBottomLeft,
        });
}

void BlockParts::paintEvent(QPaintEvent *)
{
    const QColor color(palette().color(QPalette::Accent));
    const QPen border(palette().color(QPalette::Text), 2, Qt::SolidLine, Qt::FlatCap);

    // int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.translate(width() / 2., height() / 2.);
    // painter.scale(side / 200.0, side / 200.0);

    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(shape.data(), shape.size());

    painter.setPen(border);
    painter.drawPolyline(shape.data(), 2);
    painter.drawPolyline(&shape.data()[2], shape.size() - 2);
}
