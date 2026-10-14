#include "mainwidget.h"

MainWidget::MainWidget(ShapeObjectsEditor* manager, QWidget* parent):
    QWidget(parent), manager(manager) {}


void MainWidget::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        manager->OnMousePress(event);
        update();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent* event) {
    manager->OnMouseMove(event);
    update();
}

void MainWidget::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        manager->OnMouseRelease(event);
        update();
    }
}

void MainWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    manager->OnPaint(&painter);
}