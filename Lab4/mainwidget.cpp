#include "mainwidget.h"
#include "globaleditor.h"

MainWidget::MainWidget(QWidget* parent):
    QWidget(parent) {}

void MainWidget::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        globalEditor.OnMousePress(event);
        update();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent* event) {
    globalEditor.OnMouseMove(event);
    update();
}

void MainWidget::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        globalEditor.OnMouseRelease(event);
        update();
    }
}

void MainWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    globalEditor.OnPaint(&painter);
}