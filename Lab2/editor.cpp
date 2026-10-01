#include "editor.h"

Editor::Editor() {
    shape = nullptr;
}

Editor::~Editor() {
    if (shape != nullptr) {
        delete shape;
    }
}

Shape* Editor::getRubberShape() {
    return shape;
}

void Editor::resetShape() {
    shape = nullptr;
}

void Editor::onMouseMove(QMouseEvent* event) {
    if (shape != nullptr) {
        shape->setEndCoords(event->pos().x(), event->pos().y());
    }
}

void Editor::onMouseRelease(QMouseEvent* event) {
    if (shape == nullptr) return;

    shape->setEndCoords(event->pos().x(), event->pos().y());
    shape->setIsRubber(false);

    if (shape->getCoords().width() == 0 && shape->getCoords().height() == 0 && shape->getName() != "Крапка") {
        delete shape;
        shape = nullptr;
    }
}

void RectEditor::onMousePress(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        shape = new RectShape();
        shape->setCoords(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
        shape->setIsRubber(true);
    }
}

void LineEditor::onMousePress(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        shape = new LineShape();
        shape->setCoords(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
        shape->setIsRubber(true);
    }
}

void EllipseEditor::onMousePress(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        shape = new EllipseShape();
        shape->setCoords(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
        shape->setIsRubber(true);
    }
}

void PointEditor::onMousePress(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        shape = new PointShape();
        shape->setCoords(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
        shape->setIsRubber(true);
    }
}