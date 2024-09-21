#pragma once

#include <QBoxLayout>
#include <QWidget>
#include <QLabel>

class BlockWidget : public QWidget
{
    Q_OBJECT

public:
    BlockWidget(QWidget *parent = nullptr);

    // QSize sizeHint() const override;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint dragPosition;
    QBoxLayout layout;
    QLabel label;
};
