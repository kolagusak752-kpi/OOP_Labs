#include "shape.h"
#include <math.h>
Shape::Shape() {}

void Shape::setCoords(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

void Shape::setEndCoords(int x, int y) {
    this->x2 = x;
    this->y2 = y;
}

QRect Shape::getCoords() {
    QRect rect(x1,y1,x2-x1,y2-y1);
    return rect;
}

void Shape::setIsRubber(bool value) {
    isRubber = value;
}

void Shape::setColor(QColor c) {
    color = c;
}

void PointShape::draw(QPainter* painter) {
    painter->setPen(QPen(color, 5, Qt::SolidLine));
    painter->drawPoint(x1,y1);
}

void RectShape::draw(QPainter* painter) {
    int width = (this->x2 - this->x1) * 2;
    int height = (this->y2 - this->y1) * 2;
    int xStart, yStart;
    if(width < 0) {
        xStart = x1 + width/2;
    } else {
        xStart = x1 - width/2;
    }
    if(height < 0) {
        yStart = y1 - height/2;
    } else {
        yStart = y1 + height/2;
    }
    if(isRubber) {
        painter->setBrush(QBrush(Qt::NoBrush));
        painter->setPen(QPen(QColor(Qt::red), 3, Qt::SolidLine ));
    } else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
        painter->setBrush(QBrush(Qt::NoBrush));
    }
    painter->drawRect(xStart, yStart, width, height);
}

void EllipseShape::draw(QPainter* painter) {
    int width = this->x2 - this->x1;
    int height = this->y2 - this->y1;
    if(isRubber) {
        painter->setBrush(QBrush(Qt::NoBrush));
        painter->setPen(QPen(QColor(Qt::red), 3, Qt::SolidLine ));
    } else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
        painter->setBrush(QBrush(QColor(Qt::cyan), Qt::SolidPattern));
    }
    painter->drawEllipse(this->x1, this->y1, width, height);
}

void LineShape::draw(QPainter* painter) {
    painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
    painter->drawLine(this->x1, this->y1, this->x2, this->y2);
}

QString LineShape::getName() {
    return "Лінія";
};
QString EllipseShape::getName() {
    return "Еліпс";
};
QString RectShape::getName() {
    return "Прямокутник";
};
QString PointShape::getName() {
    return "Крапка";
}

