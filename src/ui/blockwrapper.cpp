#include "blockwrapper.h"
#include "blockparts.h"
#include "ui/blockparts.h"

#include <QMouseEvent>
#include <QPainter>

BlockWrapper::BlockWrapper(QWidget *parent)
    : QWidget(parent)
    , layout(QBoxLayout::TopToBottom, this)
{
    layout.setSpacing(0);
    layout.setContentsMargins(0, 0, 0, 0);
    layout.setSizeConstraint(QLayout::SetFixedSize);
    // setContextMenuPolicy(Qt::ActionsContextMenu);
    // setToolTip(tr("Bloque!"));
}

void BlockWrapper::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void BlockWrapper::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

void paintBlockShape(QPainter &painter, int width, int height, BlockParts::Decoration top, BlockParts::Decoration bottom, QColor fill, QColor border) {
    static std::vector<QPoint> shape; // Reuse allocations
    shape.clear();
    
    static const int slopeW = NOTCH_HEIGHT * NOTCH_INV_SLOPE;
    static const QPoint slopePoints[] = {
        QPoint(NOTCH_LEFT_GAP, 0),
        QPoint(NOTCH_LEFT_GAP + slopeW, NOTCH_HEIGHT),
        QPoint(NOTCH_LEFT_GAP + NOTCH_WIDTH - slopeW, NOTCH_HEIGHT),
        QPoint(NOTCH_LEFT_GAP + NOTCH_WIDTH, 0),
    };
    
    const QPoint offsetTopLeft = 
        (top & BlockParts::Offset
            ? QPoint(NOTCH_LEFT_GAP * 2, 0) : QPoint(0, 0));
    const QPoint offsetBottomLeft =
        (bottom & BlockParts::Offset
            ? QPoint(NOTCH_LEFT_GAP * 2, height) : QPoint(0, height));
    
    shape.assign({
        QPoint(0, height),
        QPoint(0, 0),
        offsetTopLeft,
    });
    
    if (top & BlockParts::Notched)
        shape.insert(shape.end(), {
            offsetTopLeft + slopePoints[0],
            offsetTopLeft + slopePoints[1],
            offsetTopLeft + slopePoints[2],
            offsetTopLeft + slopePoints[3],
        });
    
    shape.insert(shape.end(), {
        QPoint(width, 0),
        QPoint(width, height),
    });
    
    if (bottom & BlockParts::Notched)
        shape.insert(shape.end(), {
            offsetBottomLeft + slopePoints[3],
            offsetBottomLeft + slopePoints[2],
            offsetBottomLeft + slopePoints[1],
            offsetBottomLeft + slopePoints[0],
            offsetBottomLeft,
        });
    
    const QPen borderPen(border, 2, Qt::SolidLine, Qt::FlatCap);
    
    painter.setBrush(fill);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(shape.data(), shape.size());
    
    painter.setPen(borderPen);
    painter.drawPolyline(shape.data(), 2);
    painter.drawPolyline(&shape.data()[2], shape.size() - 2);
}

void BlockWrapper::paintEvent(QPaintEvent *)
{
    const QColor fill(0x0000ff);
    const QColor border(0xffff00);
 
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    for (auto child : findChildren<BlockParts*>()) {
        auto rect = child->contentsRect();
        painter.save();
        painter.translate(rect.topLeft() + child->pos());
        paintBlockShape(painter, rect.width(), rect.height(), child->top, child->bottom, fill, border);
        painter.restore();
    }
}
