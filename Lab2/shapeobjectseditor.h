#pragma once

#include "editor.h"
#include <QPainter>
#include <QColor>

#define SHAPES_LIMIT 109

class ShapeObjectsEditor {
private:
    Shape** shapes;
    int shapeCount;
    Editor* currentEditor;
    QColor currentColor;

public:
    ShapeObjectsEditor();
    ~ShapeObjectsEditor();

    void StartRectEditor();
    void StartLineEditor();
    void StartEllipseEditor();
    void StartPointEditor();

    void OnMousePress(QMouseEvent* event);
    void OnMouseMove(QMouseEvent* event);
    void OnMouseRelease(QMouseEvent* event);
    void OnPaint(QPainter* painter);

    void RemoveLastShape();
    void setCurrentColor(QColor c);
};