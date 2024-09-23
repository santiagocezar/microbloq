#pragma once

#include <QBoxLayout>
#include <QWidget>

class BlockWrapper : public QWidget
{
    Q_OBJECT

public:
    BlockWrapper(QWidget *parent = nullptr);
    QBoxLayout layout;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPoint dragPosition;
};
