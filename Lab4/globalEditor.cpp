#include "globaleditor.h"
#define SHAPES_LIMIT 110

GlobalEditor globalEditor;
GlobalEditor::GlobalEditor() {
    shapes = new Shape*[SHAPES_LIMIT];
    shapeCount = 0;
    templateShape = nullptr;
    currentShape = nullptr;
    currentColor = Qt::black;
}

GlobalEditor::~GlobalEditor() {
    for(int i = 0; i < shapeCount; i++) {
        delete shapes[i];
    }
    delete[] shapes;
    if (templateShape != nullptr) {
        delete templateShape;
    }
    if(currentShape != nullptr) {
        delete currentShape;
    }
}

void GlobalEditor::OnStart(Shape* templShape) {
    if(templateShape != nullptr) {
        delete templateShape;
    }
    templateShape = templShape;
}

void GlobalEditor::OnMousePress(QMouseEvent* event) {
    if(templateShape != nullptr) {
            currentShape = templateShape->getShape();
            currentShape->setCoords(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y());
            currentShape->setIsRubber(true);
            currentShape->setColor(currentColor);
}
}

void GlobalEditor::OnMouseMove(QMouseEvent* event) {
    if (currentShape != nullptr) {
        currentShape->setEndCoords(event->pos().x(), event->pos().y());
    }
}

void GlobalEditor::OnMouseRelease(QMouseEvent* event) {
    if (currentShape != nullptr) {
        currentShape->setEndCoords(event->pos().x(), event->pos().y());
        currentShape->setIsRubber(false);
        if(!currentShape->isValid()) {
            delete currentShape;
        }
        else{
            if(shapeCount < SHAPES_LIMIT) {
                shapes[shapeCount++] = currentShape;
            }
        }
        currentShape = nullptr;
    }
}

void GlobalEditor::OnPaint(QPainter* painter) {
    for (int i = 0; i < shapeCount; i++) {
        shapes[i]->draw(painter);
    }

    if(currentShape != nullptr) {
        currentShape->draw(painter);
    }
}

void GlobalEditor::RemoveLastShape() {
    if(shapeCount > 0) {
        delete shapes[shapeCount - 1];
        shapes[shapeCount - 1] = nullptr;
        shapeCount--;
    }
}

void GlobalEditor::setCurrentColor(QColor c) {
    currentColor = c;
}