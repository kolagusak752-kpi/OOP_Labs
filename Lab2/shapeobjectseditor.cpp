#include "shapeobjectseditor.h"

ShapeObjectsEditor::ShapeObjectsEditor() {
    shapes = new Shape*[SHAPES_LIMIT];
    shapeCount = 0;
    currentEditor = nullptr;
    currentColor = Qt::black;
}

ShapeObjectsEditor::~ShapeObjectsEditor() {
    for(int i = 0; i < shapeCount; i++) {
        delete shapes[i];
    }
    delete[] shapes;

    if (currentEditor != nullptr) {
        delete currentEditor;
    }
}

void ShapeObjectsEditor::StartRectEditor() {
    if (currentEditor != nullptr) delete currentEditor;
    currentEditor = new RectEditor();
}

void ShapeObjectsEditor::StartLineEditor() {
    if (currentEditor != nullptr) delete currentEditor;
    currentEditor = new LineEditor();
}

void ShapeObjectsEditor::StartEllipseEditor() {
    if (currentEditor != nullptr) delete currentEditor;
    currentEditor = new EllipseEditor();
}

void ShapeObjectsEditor::StartPointEditor() {
    if (currentEditor != nullptr) delete currentEditor;
    currentEditor = new PointEditor();
}

void ShapeObjectsEditor::OnMousePress(QMouseEvent* event) {
    if (currentEditor != nullptr) {
        currentEditor->onMousePress(event);
        Shape* tempShape = currentEditor->getRubberShape();
        if (tempShape != nullptr) {
            tempShape->setColor(currentColor);
        }
    }
}

void ShapeObjectsEditor::OnMouseMove(QMouseEvent* event) {
    if (currentEditor != nullptr) {
        currentEditor->onMouseMove(event);
    }
}

void ShapeObjectsEditor::OnMouseRelease(QMouseEvent* event) {
    if (currentEditor != nullptr) {
        currentEditor->onMouseRelease(event);

        Shape* finishedShape = currentEditor->getRubberShape();

        if (finishedShape != nullptr) {
            if (shapeCount < SHAPES_LIMIT) {
                shapes[shapeCount] = finishedShape;
                shapeCount++;
            } else {
                delete finishedShape;
            }
            currentEditor->resetShape();
        }
    }
}

void ShapeObjectsEditor::OnPaint(QPainter* painter) {
    for (int i = 0; i < shapeCount; i++) {
        shapes[i]->draw(painter);
    }

    if (currentEditor != nullptr && currentEditor->getRubberShape() != nullptr) {
        currentEditor->getRubberShape()->draw(painter);
    }
}

void ShapeObjectsEditor::RemoveLastShape() {
    if(shapeCount > 0) {
        delete shapes[shapeCount - 1];
        shapes[shapeCount - 1] = nullptr;
        shapeCount--;
    }
}

void ShapeObjectsEditor::setCurrentColor(QColor c) {
    currentColor = c;
}