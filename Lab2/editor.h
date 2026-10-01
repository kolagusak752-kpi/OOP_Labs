#pragma once

#include "shape.h"
#include <QMouseEvent>

class Editor
{
protected:
    Shape* shape;
public:
    Editor();
    virtual ~Editor();

    virtual void onMousePress(QMouseEvent* event) = 0;
    virtual void onMouseMove(QMouseEvent* event);
    virtual void onMouseRelease(QMouseEvent* event);

    Shape* getRubberShape();
    void resetShape();
};

class RectEditor : public Editor
{
public:
    void onMousePress(QMouseEvent* event) override;
};

class LineEditor : public Editor
{
public:
    void onMousePress(QMouseEvent* event) override;
};

class EllipseEditor : public Editor
{
public:
    void onMousePress(QMouseEvent* event) override;
};

class PointEditor : public Editor
{
public:
    void onMousePress(QMouseEvent* event) override;
};