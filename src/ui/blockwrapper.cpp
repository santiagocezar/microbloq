#include "blockwrapper.h"
#include "blockparts.h"
#include "ui/blockparts.h"

#include <QMouseEvent>

BlockWrapper::BlockWrapper(QWidget *parent)
    : QWidget(parent)
    , layout(QBoxLayout::TopToBottom, this)
{
    layout.setSpacing(-100);
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
