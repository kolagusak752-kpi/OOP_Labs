#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globaleditor.h"
#include <QPainter>
#include <QColorDialog>
#include "mainwidget.h"
#include "QActionGroup"
#include <QSize>
#include <ios>
#include <fstream>

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
    ui->figurestable->setIcon(QIcon(":/icons/figurestable.svg"));
    
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    widget = new MainWidget(this);
    widget->setMouseTracking(true);
    this->setCentralWidget(widget);
    connect(widget, &MainWidget::shapeAdded, this, &MainWindow::on_shape_added);

    this->figuresTable = new FiguresTable(this);
    connect(figuresTable, &FiguresTable::selectionChanged, this, &MainWindow::syncCanvasSelection);
    connect(figuresTable, &FiguresTable::shapeDeleted, this, &MainWindow::onShapeDeletedFromTable);

    QActionGroup* toolsGroup = new QActionGroup(this);
    toolsGroup->setExclusive(true);
    toolsGroup->addAction(ui->ellipse);
    toolsGroup->addAction(ui->line);
    toolsGroup->addAction(ui->point);
    toolsGroup->addAction(ui->rectangle);
    toolsGroup->addAction(ui->cube);
    toolsGroup->addAction(ui->lineOO);

    loadShapesFromFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_line_triggered()
{
    GlobalEditor::getInstance().OnStart(new LineShape());
    this->setWindowTitle("Поточний об'єкт: Лінія");
}

void MainWindow::on_rectangle_triggered()
{
    GlobalEditor::getInstance().OnStart(new RectShape());
    this->setWindowTitle("Поточний об'єкт: Прямокутник");
}


void MainWindow::on_ellipse_triggered()
{
    GlobalEditor::getInstance().OnStart(new EllipseShape);
    this->setWindowTitle("Поточний об'єкт: Еліпс");
}

void MainWindow::on_point_triggered()
{
    GlobalEditor::getInstance().OnStart(new PointShape());
    this->setWindowTitle("Поточний об'єкт: Крапка");
}

void MainWindow::on_back_triggered()
{

    if (GlobalEditor::getInstance().RemoveLastShape()) {

        figuresTable->removeLast();
        std::ifstream inFile("../../shapesObjectData.txt");
        std::vector<std::string> lines;
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                lines.push_back(line);
            }
            inFile.close();
        }


        if (!lines.empty()) {
            lines.pop_back();

            std::ofstream outFile("../../shapesObjectData.txt", std::ios::trunc);
            if (outFile.is_open()) {
                for (const std::string& l : lines) {
                    outFile << l << "\n";
                }
                outFile.close();
            }
        }

        update();
    }
}


void MainWindow::on_color_triggered()
{
    QColor chosenColor = QColorDialog::getColor(Qt::black, nullptr,"Виберіть колір");
    if(chosenColor.isValid()) {
        GlobalEditor::getInstance().setCurrentColor(chosenColor);
    }

}
void MainWindow::on_cube_triggered()
{
    GlobalEditor::getInstance().OnStart(new CubeShape());
    this->setWindowTitle("Поточний об'єкт: Куб");
}


void MainWindow::on_lineOO_triggered()
{
    GlobalEditor::getInstance().OnStart(new LineOOShape());
    this->setWindowTitle("Поточний об'єкт: Лінія з кружечками");
}

void MainWindow::on_shape_added()
{
    Shape* lastShape = GlobalEditor::getInstance().getLastShape();
    if(lastShape != nullptr) {
    QRect rect = lastShape->getCoords();
    QString name = lastShape->getName();
    int x1 = rect.left();
    int y1 = rect.top();
    int x2 = rect.right();
    int y2 = rect.bottom();
        figuresTable->add(name, x1, y1, x2, y2);
    std::ofstream outFile("../../shapesObjectData.txt", std::ios::app);
        if(outFile.is_open()) {
        std::string stdName = name.toStdString();
        outFile << stdName << "\t" << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << "\n";
        outFile.close();
        };
    }
}

void MainWindow::on_figurestable_triggered()
{
    figuresTable->show();
}

void MainWindow::syncCanvasSelection(QList<int> rows) {
    GlobalEditor::getInstance().syncSelection(rows);
    widget->update();
}

void MainWindow::onShapeDeletedFromTable(int index) {

    GlobalEditor::getInstance().removeShape(index);
    std::vector<std::string> lines;
    std::ifstream inFile("../../shapesObjectData.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
    }


    if (index >= 0 && index < lines.size()) {
        lines.erase(lines.begin() + index);

        std::ofstream outFile("../../shapesObjectData.txt", std::ios::trunc);
        if (outFile.is_open()) {
            for (const std::string& l : lines) {
                outFile << l << "\n";
            }
            outFile.close();
        }
    }

    widget->update();
}

void MainWindow::loadShapesFromFile() {
    std::ifstream file("../../shapesObjectData.txt");

    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        QString qLine = QString::fromStdString(line);
        QStringList parts = qLine.split('\t');

        if (parts.size() >= 5) {
            QString name = parts[0];
            int x1 = parts[1].toInt();
            int y1 = parts[2].toInt();
            int x2 = parts[3].toInt();
            int y2 = parts[4].toInt();

            Shape* newShape = nullptr;

            if (name == "Лінія") newShape = new LineShape();
            else if (name == "Прямокутник") newShape = new RectShape();
            else if (name == "Еліпс") newShape = new EllipseShape();
            else if (name == "Крапка") newShape = new PointShape();
            else if (name == "Лінія з кружечками") newShape = new LineOOShape();
            else if (name == "Куб") newShape = new CubeShape();

            if (newShape != nullptr) {
                newShape->setCoords(x1, y1, x2, y2);
                GlobalEditor::getInstance().addShape(newShape);
                figuresTable->add(name, x1, y1, x2, y2);
            }
        }
    }
    file.close();
    widget->update();
}