#pragma once
#include <QPainter>
#include <QRect>


class Shape
{
protected:
    int x1, x2, y1, y2;
    QColor color;
    bool isRubber;
public:
    Shape();
    virtual ~Shape() {}
    void setColor(QColor c);
    void setCoords(int x1, int y1, int x2, int y2);
    void setEndCoords(int x, int y);
    void setIsRubber(bool value);
    QRect getCoords();
    virtual void draw(QPainter* painter) = 0;
    virtual QString getName() = 0;
};
class PointShape : public Shape
{
public:
    void draw(QPainter* painter) override;
    QString getName() override;
};

class RectShape : public Shape
{
public:
    void draw(QPainter* painter) override;
    QString getName() override;
};

class EllipseShape : public Shape
{
public:
    void draw(QPainter* painter) override;
    QString getName() override;
};

class LineShape : public Shape
{
public:
    void draw(QPainter* painter) override;
    QString getName() override;
};
