#include "mainwidget.h"
#include "globaleditor.h"

MainWidget::MainWidget(QWidget* parent):
    QWidget(parent) {}

void MainWidget::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        GlobalEditor::getInstance().OnMousePress(event);
        update();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent* event) {
    GlobalEditor::getInstance().OnMouseMove(event);
    update();
}

void MainWidget::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        bool added = GlobalEditor::getInstance().OnMouseRelease(event);
        update();
        if(added) {
            emit shapeAdded();
        }
    }
}

void MainWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    GlobalEditor::getInstance().OnPaint(&painter);
}