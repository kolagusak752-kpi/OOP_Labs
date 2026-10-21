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

bool Shape::isValid() {
    bool isVal = x1 != x2 && y1 != y2;
    return isVal;
}

bool PointShape::isValid() {
    return true;
}

Shape* PointShape::getShape() {
    return new PointShape();
}
Shape* EllipseShape::getShape() {
    return new EllipseShape();
}
Shape* RectShape::getShape() {
    return new RectShape();
}
Shape* LineShape::getShape() {
    return new LineShape();
}
Shape* LineOOShape::getShape() {
    return new LineOOShape();
}
Shape* CubeShape::getShape() {
    return new CubeShape();
}
void PointShape::draw(QPainter* painter) {
    painter->setPen(QPen(color, 5, Qt::SolidLine));
    painter->drawPoint(x1,y1);
}

void RectShape::draw(QPainter* painter) {
    int rx = std::abs(this->x2 - this->x1);
    int ry = std::abs(this->y2 - this->y1);

    int xStart = this->x1 - rx;
    int yStart = this->y1 - ry;
    int width  = rx * 2;
    int height = ry * 2;

    if (isRubber) {
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
    } else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
    }

    painter->drawRect(xStart, yStart, width, height);
}

void EllipseShape::draw(QPainter* painter) {
    painter->save();
    int width = this->x2 - this->x1;
    int height = this->y2 - this->y1;
    if(isRubber) {
        painter->setPen(QPen(QColor(Qt::red), 3, Qt::DashLine ));
    } else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
        painter->setBrush(QBrush(QColor(Qt::cyan), Qt::SolidPattern));
    }
    painter->drawEllipse(this->x1, this->y1, width, height);
    painter->restore();
}

void LineShape::draw(QPainter* painter) {
    if(isRubber) {
        painter->setPen(QPen(QColor(Qt::red), 3, Qt::DashLine ));
    }   else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
    }
    painter->drawLine(this->x1, this->y1, this->x2, this->y2);
}

void LineOOShape::draw(QPainter* painter) {
    if(isRubber) {
        painter->setPen(QPen(QColor(Qt::red), 3, Qt::DashLine ));
    }   else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
    }
    int origX1 = x1, origY1 = y1, origX2 = x2, origY2 = y2;
    LineShape::draw(painter);
    painter->save();
    painter->setBrush(QBrush(Qt::white));
    int R = 15;
    setCoords(origX1 - R, origY1 - R, origX1 + R, origY1 + R);
    EllipseShape::draw(painter);
    setCoords(origX2 - R, origY2 - R, origX2 + R, origY2 + R);
    EllipseShape::draw(painter);
    setCoords(origX1, origY1, origX2, origY2);
    painter->restore();
}

void CubeShape::draw(QPainter* painter) {
    if(isRubber) {
        painter->setPen(QPen(QColor(Qt::red), 3, Qt::DashLine ));
    }   else {
        painter->setPen(QPen(QColor(color), 3, Qt::SolidLine ));
    }
        int origX1 = x1, origY1 = y1, origX2 = x2, origY2 = y2;

        int rx = std::abs(origX2 - origX1);
        int ry = std::abs(origY2 - origY1);

        int offsetX = rx / 2;
        int offsetY = ry / 2;

        int leftX = origX1 - rx;
        int rightX = origX1 + rx;
        int topY = origY1 - ry;
        int bottomY = origY1 + ry;

        setCoords(origX1 + offsetX, origY1 + offsetY, origX2 + offsetX, origY2 + offsetY);
        RectShape::draw(painter);

        setCoords(leftX, topY, leftX + offsetX, topY + offsetY);
        LineShape::draw(painter);

        setCoords(leftX, bottomY, leftX + offsetX, bottomY + offsetY);
        LineShape::draw(painter);

        setCoords(rightX, bottomY, rightX + offsetX, bottomY + offsetY);
        LineShape::draw(painter);

        setCoords(rightX, topY, rightX + offsetX, topY + offsetY);
        LineShape::draw(painter);

        setCoords(origX1, origY1, origX2, origY2);
        RectShape::draw(painter);

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
QString LineOOShape::getName() {
    return "Лінія з кружечками";
}
QString CubeShape::getName() {
    return "Куб";
}


