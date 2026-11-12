#pragma once
#include "QWidget"


class MainWidget : public QWidget {
    Q_OBJECT
signals:
    void shapeAdded();
public:
    MainWidget(QWidget* parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
};
