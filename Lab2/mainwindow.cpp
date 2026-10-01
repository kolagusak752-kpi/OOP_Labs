#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColorDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new ShapeObjectsEditor();
    manager->StartLineEditor();
    this->setWindowTitle("Поточний об'єкт: Лінія");
}

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    manager->OnPaint(&painter);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        manager->OnMousePress(event);
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    manager->OnMouseMove(event);
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        manager->OnMouseRelease(event);
        update();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        manager->StartLineEditor();
        this->setWindowTitle("Поточний об'єкт: Лінія");
        break;
    case 1:
        manager->StartRectEditor();
        this->setWindowTitle("Поточний об'єкт: Прямокутник");
        break;
    case 2:
        manager->StartEllipseEditor();
        this->setWindowTitle("Поточний об'єкт: Еліпс");
        break;
    case 3:
        manager->StartPointEditor();
        this->setWindowTitle("Поточний об'єкт: Крапка");
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    manager->RemoveLastShape();
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor chosenColor = QColorDialog::getColor(Qt::black, this, "Виберіть колір");
    if(chosenColor.isValid()) {
        manager->setCurrentColor(chosenColor);
    }
}

