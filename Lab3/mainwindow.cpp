#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColorDialog>
#include "mainwidget.h"
#include "QActionGroup"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new ShapeObjectsEditor();
    manager->StartLineEditor();
    this->setWindowTitle("Поточний об'єкт: Лінія");

    MainWidget* widget = new MainWidget(manager, this);
    widget->setMouseTracking(true);
    this->setCentralWidget(widget);

    QActionGroup* toolsGroup = new QActionGroup(this);
    toolsGroup->setExclusive(true);
    toolsGroup->addAction(ui->ellipse);
    toolsGroup->addAction(ui->line);
    toolsGroup->addAction(ui->point);
    toolsGroup->addAction(ui->rectangle);
    ui->line->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

void MainWindow::on_line_triggered()
{
    manager->StartLineEditor();
    this->setWindowTitle("Поточний об'єкт: Лінія");
}

void MainWindow::on_rectangle_triggered()
{
    manager->StartRectEditor();
    this->setWindowTitle("Поточний об'єкт: Прямокутник");
}


void MainWindow::on_ellipse_triggered()
{
    manager->StartEllipseEditor();
    this->setWindowTitle("Поточний об'єкт: Еліпс");
}

void MainWindow::on_point_triggered()
{
    manager->StartPointEditor();
    this->setWindowTitle("Поточний об'єкт: Крапка");
}

void MainWindow::on_back_triggered()
{
    manager->RemoveLastShape();
    update();
}



void MainWindow::on_color_triggered()
{
    QColor chosenColor = QColorDialog::getColor(Qt::black, nullptr,"Виберіть колір");
    if(chosenColor.isValid()) {
        manager->setCurrentColor(chosenColor);
    }

}