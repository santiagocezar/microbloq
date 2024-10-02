#pragma once

#include <vector>
#include <QBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

const int NOTCH_LEFT_GAP = 8;
const int NOTCH_WIDTH = 16;
const int NOTCH_HEIGHT = 6;
const float NOTCH_INV_SLOPE = .5;
const int BORDER_THICKNESS = 2;

class BlockParts : public QWidget
{
    Q_OBJECT

public:

    enum Decoration {
        None = 0,
        Notched = 1,
        Offset = 2,
    };

    
    BlockParts(Decoration top = Decoration::None, Decoration bottom = Decoration::None, QWidget *parent = nullptr);

    Decoration top, bottom;

private:

    QBoxLayout layout;
    QLabel label;
    QLineEdit input;
};

inline BlockParts::Decoration operator|(BlockParts::Decoration a, BlockParts::Decoration b)
{
    return static_cast<BlockParts::Decoration>(static_cast<int>(a) | static_cast<int>(b));
}
