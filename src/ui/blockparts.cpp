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

    // setContentsMargins(BORDER_THICKNESS, BORDER_THICKNESS, BORDER_THICKNESS, BORDER_THICKNESS);
    setContentsMargins(BORDER_THICKNESS / 2, BORDER_THICKNESS / 2, BORDER_THICKNESS / 2, BORDER_THICKNESS / 2);
    adjustSize();

    setAttribute(Qt::WA_TranslucentBackground);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setToolTip(tr("Bloque!"));
}
