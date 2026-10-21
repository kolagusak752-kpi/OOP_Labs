#pragma once
#include <QPainter>
#include <QRect>
#include <QMouseEvent>

class Shape
{
protected:
    int x1, x2, y1, y2;
    QColor color;
    bool isRubber;
public:
    Shape();
    virtual ~Shape() {}
    virtual Shape* getShape() = 0;
    void setColor(QColor c);
    void setCoords(int x1, int y1, int x2, int y2);
    void setEndCoords(int x, int y);
    void setIsRubber(bool value);
    virtual bool isValid();
    QRect getCoords();
    virtual void draw(QPainter* painter) = 0;
    virtual QString getName() = 0;
};
class PointShape : virtual public Shape
{
public:
    virtual bool isValid() override;
    void draw(QPainter* painter) override;
    Shape* getShape() override;
    QString getName() override;
};

class RectShape : virtual public Shape
{
public:

    void draw(QPainter* painter) override;
    Shape* getShape() override;
    QString getName() override;
};

class EllipseShape : virtual public Shape
{
public:

    void draw(QPainter* painter) override;
    Shape* getShape() override;
    QString getName() override;
};

class LineShape : virtual public Shape
{
public:

    void draw(QPainter* painter) override;
    Shape* getShape() override;
    QString getName() override;
};

class LineOOShape : public LineShape, public EllipseShape {
    void draw(QPainter* painter) override;
    Shape* getShape() override;
    QString getName() override;
};

class CubeShape : public LineShape, public RectShape {
    void draw(QPainter* painter) override;
    Shape* getShape() override;
    QString getName() override;
};
