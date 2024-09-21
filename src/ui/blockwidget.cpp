#include "blockwidget.h"

#include <QMouseEvent>
#include <QPainter>
#include "qnamespace.h"

BlockWidget::BlockWidget(QWidget *parent)
    : QWidget(parent)
    , layout(QBoxLayout::LeftToRight, this)
    , label("Hola!")
{
    layout.addWidget(&label);
    this->adjustSize();

    setAttribute(Qt::WA_TranslucentBackground);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setToolTip(tr("Bloque!"));
}

void BlockWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void BlockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}
void BlockWidget::paintEvent(QPaintEvent *)
{
    auto rect = this->rect();
    const QPoint blockShape[] = {
        QPoint(rect.left(), rect.top()),
        QPoint(rect.right()+1, rect.top()),
        QPoint(rect.right()+1, rect.bottom()+1),
        QPoint(rect.left(), rect.bottom()+1),
    };

    qDebug() << blockShape[0] << blockShape[2];

    const QColor color(palette().color(QPalette::Accent));
    const QPen border(palette().color(QPalette::Text), 2, Qt::SolidLine, Qt::FlatCap);

    // int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.translate(width() / 2., height() / 2.);
    // painter.scale(side / 200.0, side / 200.0);

    painter.save();
    painter.setBrush(color);
    painter.drawConvexPolygon(blockShape, 4);
    painter.restore();
    painter.setPen(border);
    painter.drawConvexPolygon(blockShape, 4);
}
