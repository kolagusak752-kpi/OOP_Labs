#pragma once
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include "figurestable.h"
#include "mainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_line_triggered();

    void on_rectangle_triggered();

    void on_back_triggered();

    void on_color_triggered();

    void on_ellipse_triggered();

    void on_point_triggered();

    void on_cube_triggered();

    void on_lineOO_triggered();

    void on_shape_added();

    void syncCanvasSelection(QList<int> rows);

    void on_figurestable_triggered();

    void onShapeDeletedFromTable(int index);

    void on_uploadFile_triggered();

private:
    Ui::MainWindow *ui;
    FiguresTable* figuresTable;
    MainWidget* widget;
    std::string currentFilePath = "../../shapesObjectData.txt";
    bool loadShapesFromFile(std::string path);
};


