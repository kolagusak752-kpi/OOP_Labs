#pragma once
#include "QWidget"
#include "shapeobjectseditor.h"

class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget(ShapeObjectsEditor* manager, QWidget* parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
private:
    ShapeObjectsEditor* manager;
};
