#pragma once

#include <vector>
#include <QBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

const int NOTCH_LEFT_GAP = 6;
const int NOTCH_WIDTH = 14;
const int NOTCH_HEIGHT = 4;
const float NOTCH_INV_SLOPE = .5;
const int BORDER_THICKNESS = 2;

class BlockParts : public QWidget
{
    Q_OBJECT

public:

    enum Decoration {
        Notch,
        Offset,
        Flat,
    };


    BlockParts(Decoration top = Decoration::Notch, Decoration bottom = Decoration::Notch, QWidget *parent = nullptr);

    // QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateShape();

    Decoration top, bottom;
    std::vector<QPoint> shape;
    QBoxLayout layout;
    QLabel label;
    QLineEdit input;
};
