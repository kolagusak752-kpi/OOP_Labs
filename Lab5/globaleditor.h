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
    GlobalEditor();

public:
    ~GlobalEditor();
    static GlobalEditor& getInstance();
    void OnStart(Shape* templShape);

    void OnMousePress(QMouseEvent* event);
    void OnMouseMove(QMouseEvent* event);
    bool OnMouseRelease(QMouseEvent* event);
    void OnPaint(QPainter* painter);
    void removeShape(int index);
    bool RemoveLastShape();
    void setCurrentColor(QColor c);
    void syncSelection(QList<int> selectedIndexes);
    void addShape(Shape* shape);
    void clear();

    Shape* getLastShape();

};

