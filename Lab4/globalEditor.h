#pragma once
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include "shape.h"

class GlobalEditor {
private:
    Shape** shapes;
    int shapeCount;
    Shape* templateShape;
    Shape* currentShape;
    QColor currentColor;

public:
    GlobalEditor();
    ~GlobalEditor();

    void OnStart(Shape* templShape);

    void OnMousePress(QMouseEvent* event);
    void OnMouseMove(QMouseEvent* event);
    void OnMouseRelease(QMouseEvent* event);
    void OnPaint(QPainter* painter);

    void RemoveLastShape();
    void setCurrentColor(QColor c);
};

extern GlobalEditor globalEditor;