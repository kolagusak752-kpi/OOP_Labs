#include "globaleditor.h"
#define SHAPES_LIMIT 110

GlobalEditor::GlobalEditor() {
    shapes = new Shape*[SHAPES_LIMIT];
    shapeCount = 0;
    templateShape = nullptr;
    currentShape = nullptr;
    currentColor = Qt::black;
}
GlobalEditor& GlobalEditor::getInstance() {
    static GlobalEditor instance;
    return instance;
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

bool GlobalEditor::OnMouseRelease(QMouseEvent* event) {
    if (currentShape != nullptr) {
        currentShape->setEndCoords(event->pos().x(), event->pos().y());
        currentShape->setIsRubber(false);
        if(!currentShape->isValid()) {
            delete currentShape;
            currentShape = nullptr;
            return false;
        }
        if(shapeCount < SHAPES_LIMIT) {
                shapes[shapeCount++] = currentShape;
                currentShape = nullptr;
                return true;
            }
        delete currentShape;
        currentShape = nullptr;
    }
    return false;


}

void GlobalEditor::OnPaint(QPainter* painter) {
    for (int i = 0; i < shapeCount; i++) {
        shapes[i]->draw(painter);
    }

    if(currentShape != nullptr) {
        currentShape->draw(painter);
    }
}

bool GlobalEditor::RemoveLastShape() {
    if(shapeCount > 0) {
        delete shapes[shapeCount - 1];
        shapes[shapeCount - 1] = nullptr;
        shapeCount--;
        return true;
    }
    return false;
}

void GlobalEditor::setCurrentColor(QColor c) {
    currentColor = c;
};

Shape* GlobalEditor::getLastShape() {
    return shapes[shapeCount - 1];
}

void GlobalEditor::syncSelection(QList<int> selectedIndexes) {
    for (int i = 0; i < shapeCount; i++) {
        shapes[i]->setIsSelected(selectedIndexes.contains(i));
    }
}

void GlobalEditor::removeShape(int index) {
    if (index < 0 || index >= shapeCount) return;
    delete shapes[index];

    for (int i = index; i < shapeCount - 1; i++) {
        shapes[i] = shapes[i + 1];
    }

    shapes[shapeCount - 1] = nullptr;
    shapeCount--;
}

void GlobalEditor::addShape(Shape* shape) {
    if (shapeCount < SHAPES_LIMIT) {
        shapes[shapeCount] = shape;
        shapeCount++;
    }
}

void GlobalEditor::clear() {
    for(int i = 0; i < shapeCount; i++) {
        delete shapes[i];
        shapes[i] = nullptr;
    }
    shapeCount = 0;
}