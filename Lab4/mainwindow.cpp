#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globaleditor.h"
#include <QPainter>
#include <QColorDialog>
#include "mainwidget.h"
#include "QActionGroup"
#include <QSize>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setIconSize(QSize(20, 20));
    ui->line->setIcon(QIcon(":/icons/line.svg"));
    ui->rectangle->setIcon(QIcon(":/icons/rectangle.svg"));
    ui->ellipse->setIcon(QIcon(":/icons/ellipse.svg"));
    ui->point->setIcon(QIcon(":/icons/point.svg"));
    ui->cube->setIcon(QIcon(":/icons/cube.svg"));
    ui->lineOO->setIcon(QIcon(":/icons/lineOO.svg"));
    ui->back->setIcon(QIcon(":/icons/back.svg"));
    ui->color->setIcon(QIcon(":/icons/colorpalette.svg"));
    
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    MainWidget* widget = new MainWidget(this);
    widget->setMouseTracking(true);
    this->setCentralWidget(widget);

    QActionGroup* toolsGroup = new QActionGroup(this);
    toolsGroup->setExclusive(true);
    toolsGroup->addAction(ui->ellipse);
    toolsGroup->addAction(ui->line);
    toolsGroup->addAction(ui->point);
    toolsGroup->addAction(ui->rectangle);
    toolsGroup->addAction(ui->cube);
    toolsGroup->addAction(ui->lineOO);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_line_triggered()
{
    globalEditor.OnStart(new LineShape());
    this->setWindowTitle("Поточний об'єкт: Лінія");
}

void MainWindow::on_rectangle_triggered()
{
    globalEditor.OnStart(new RectShape());
    this->setWindowTitle("Поточний об'єкт: Прямокутник");
}


void MainWindow::on_ellipse_triggered()
{
    globalEditor.OnStart(new EllipseShape);
    this->setWindowTitle("Поточний об'єкт: Еліпс");
}

void MainWindow::on_point_triggered()
{
    globalEditor.OnStart(new PointShape());
    this->setWindowTitle("Поточний об'єкт: Крапка");
}

void MainWindow::on_back_triggered()
{
    globalEditor.RemoveLastShape();
    update();
}



void MainWindow::on_color_triggered()
{
    QColor chosenColor = QColorDialog::getColor(Qt::black, nullptr,"Виберіть колір");
    if(chosenColor.isValid()) {
        globalEditor.setCurrentColor(chosenColor);
    }

}
void MainWindow::on_cube_triggered()
{
    globalEditor.OnStart(new CubeShape());
    this->setWindowTitle("Поточний об'єкт: Куб");
}


void MainWindow::on_lineOO_triggered()
{
    globalEditor.OnStart(new LineOOShape());
    this->setWindowTitle("Поточний об'єкт: Лінія з кружечками");
}

